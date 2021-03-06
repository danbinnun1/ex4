#include "ParallelServer.hpp"
#include "ProblemSolver.hpp"
#include "ServerException.hpp"
#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <threads.h>
#include <unistd.h>
#include <vector>

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
//this function always checks if there is a pending connection in the queue, and if there is, it serves it.
void threadFunction(std::queue<int> &connections, ClientHandler *handler) {
  while (true) {
    pthread_mutex_lock(&g_mutex);
    if (!connections.empty()) {
      const int client = connections.front();
      connections.pop();
      pthread_mutex_unlock(&g_mutex);
      std::cout << "client connected." << std::endl;
      handler->serveClient(client);
    } else {
      pthread_mutex_unlock(&g_mutex);
    }
  }
}

void server_side::ParallelServer::open(const int port,
                                       std::unique_ptr<ClientHandler> handler) {
  std::queue<int> connectionsQueue;
  const int threadPoolSize = 100;
  std::thread threadPool[threadPoolSize];
  for (uint32_t i = 0; i < threadPoolSize; ++i) {
    threadPool[i] =
        std::thread(threadFunction, std::ref(connectionsQueue), handler.get());
  }
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    throw ServerException("socket failed.");
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    throw ServerException("bind failed.");
  }
  if (listen(server_fd, 500) < 0) {
    throw ServerException("listen failed.");
  }
  std::cout << "waiting fot connections." << std::endl;
  while (true) {
    int clientfd;
    if ((clientfd = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
      throw ServerException("accept client failed.");
    }
    pthread_mutex_lock(&g_mutex);
    connectionsQueue.push(clientfd);
    pthread_mutex_unlock(&g_mutex);
    //connection file descriptor can't reach 1024, so when it gets to 1023, we have to close it and wait for clients to finish
    if (clientfd == FD_SETSIZE - 1) {
      close(clientfd);
      std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
  }
}