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

void threadFunction(std::queue<int> &connections, ClientHandler *handler) {
  while (true) {
    pthread_mutex_lock(&g_mutex);
    if (!connections.empty()) {
      const int client = connections.front();
      connections.pop();
      pthread_mutex_unlock(&g_mutex);
      handler->serveClient(client);
    } else {
      pthread_mutex_unlock(&g_mutex);
    }
  }
}

void server_side::ParallelServer::open(const int port,
                                       std::unique_ptr<ClientHandler> handler) {
  std::queue<int> connectionsQueue;

  std::thread threadPool[100];
  for (uint32_t i = 0; i < 100; ++i) {
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
  if (listen(server_fd, 65535) < 0) {
    throw ServerException("listen failed.");
  }
  std::cout << "waiting fot connections." << std::endl;
  while (true) {
    int clientfd;
    if ((clientfd = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
      throw ServerException("accept client failed.");
    }
    std::cout << "client connected." << std::endl;
    pthread_mutex_lock(&g_mutex);
    connectionsQueue.push(clientfd);
    pthread_mutex_unlock(&g_mutex);
  }
}