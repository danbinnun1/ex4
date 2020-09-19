#include "ReaderServer.hpp"
#include "ErrorCode.hpp"
#include "MessageStructure.hpp"
#include "ProblemException.hpp"
#include "ProblemInput.hpp"
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

using namespace std::chrono;

inline bool ends_with(std::string const &value, std::string const &ending) {
  if (ending.size() > value.size())
    return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

server_side::ReaderServer::ReaderServer(const std::string &end,
                                        uint32_t maxClients, long waitTime)
    : m_end(end), m_maxClients(maxClients), m_currentClients(0),
      m_waitTime(waitTime) {}

void timer(const long waitTime, bool &finished, bool &timeoutPassed) {
  long start =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();
  while (true) {
    long current =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count();
    if (current > start + waitTime) {
      timeoutPassed = true;
      return;
    }
    if (finished) {
      timeoutPassed = false;
      return;
    }
  }
}

void readMessage(bool &finished, int connfd, char *buffer) {
  read(connfd, buffer, 1024);
  finished = true;
}
void readMessageWithTimeout(int connfd, char *buffer, bool &recievedMessage,
                            long waitTime) {
  bool finished = false;
  bool timeoutPassed = false;
  std::thread readClinetMessage(readMessage, std::ref(finished), connfd,
                                buffer);
  std::thread countTime(timer, waitTime, std::ref(finished),
                        std::ref(timeoutPassed));
  countTime.join();
  if (timeoutPassed) {
    shutdown(connfd, SHUT_RD);
    close(connfd);
    readClinetMessage.join();
    recievedMessage = false;
    std::cout << "closed client connection because timeout passes."
              << std::endl;
  } else {
    readClinetMessage.join();
    recievedMessage = true;
  }
}

void server_side::ReaderServer::serveClient(const int connfd) {

  try {
    char buffer[1024] = {0};
    bool recievedMessage;
    readMessageWithTimeout(connfd, buffer, recievedMessage, m_waitTime);
    if (!recievedMessage) {
      --m_currentClients;
      return;
    }
    std::cout << "client sent message:" << buffer << std::endl;
    std::unique_ptr<ProblemInput> input =
        std::make_unique<ProblemInput>(buffer);
    auto requestApproval = getStructure(NO_ERROR, "");
    send(connfd, requestApproval.data(), requestApproval.size(), 0);
    bool clientFinished = false;
    while (!clientFinished) {
      memset(buffer, 0, sizeof(buffer));
      readMessageWithTimeout(connfd, buffer, recievedMessage, m_waitTime);
      if (!recievedMessage) {
        --m_currentClients;
        return;
      }
      std::string row=std::string(buffer);
      std::string enter="\r\n";
      if (ends_with(row,m_end+enter)) {
        input->addRow(row.substr(0, row.size()-m_end.size()-enter.size()));
        clientFinished = true;
      } else {
        input->addRow(row);
      }
    }
    std::unique_ptr<Problem> p = input->parse();
    std::unique_ptr<Solution> s = p->solve();
    std::string solution = s->toString();
    auto message = getStructure(NO_ERROR, solution);
    send(connfd, message.data(), message.size(), 0);
    std::cout << "client finished and got message back." << std::endl;
  } catch (const ProblemException &e) {
    auto message = getStructure(e.getCode(), "");
    send(connfd, message.data(), message.size(), 0);
    std::cout << "client finished and got message back." << std::endl;

    // shutdown(connfd, SHUT_WR);
  }
  close(connfd);
  --m_currentClients;
}

void server_side::ReaderServer::open(const int port) {
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
  std::vector<std::thread> threads = {};
  while (true) {
    int clientfd;
    if ((clientfd = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
      throw ServerException("accept client failed.");
    }
    std::cout << "client connected." << std::endl;
    ++m_currentClients;
    if (m_currentClients > m_maxClients) {
      std::string response = getStructure(SERVER_IS_FULL, "");
      send(clientfd, response.data(), response.size(), 0);
      close(clientfd);
      --m_currentClients;
      std::cout << "client could not join, server is full." << std::endl;
    } else {
      threads.emplace_back(
          std::thread(&ReaderServer::serveClient, this, clientfd));
    }
    std::cout << "clients connected: " << m_currentClients
              << ". max capacity: " << m_maxClients << std::endl;
  }
}