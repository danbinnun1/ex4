#include "SerialServer.hpp"
#include "ServerException.hpp"
#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <threads.h>
#include <unistd.h>
#include "ProblemSolver.hpp"

void server_side::SerialServer::open(const int port,
                                     std::unique_ptr<ClientHandler> handler) {
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
    std::cout<<"client connected."<<std::endl;
    handler->serveClient(clientfd);
  }
}