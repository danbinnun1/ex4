#include "ReaderServer.hpp"
#include "ProblemInput.hpp"
#include <chrono>
#include <cstring>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <threads.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std::chrono;

server_side::ReaderServer::ReaderServer(const std::string &end,
                                        uint32_t maxClients, long waitTime)
    : m_end(end), m_maxClients(maxClients), m_waitTime(waitTime),
      m_currentClients(0) {}

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
  read(connfd, buffer, sizeof(buffer));
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
  } else {
    close(connfd);
    readClinetMessage.join();
    recievedMessage = true;
  }
}

void server_side::ReaderServer::serveClient(const int connfd) {
  char buffer[1024] = {0};
  bool recievedMessage;
  readMessageWithTimeout(connfd, buffer, recievedMessage, m_waitTime);
  if (!recievedMessage) {
    return;
  }
  std::unique_ptr<ProblemInput> input = std::make_unique<ProblemInput>(buffer);
  bool clientFinished = false;
  while (!clientFinished) {
    memset(buffer, 0, sizeof(buffer));
    readMessageWithTimeout(connfd, buffer, recievedMessage, m_waitTime);
    if (!recievedMessage) {
      return;
    }
    if (buffer == m_end) {
      clientFinished = true;
    } else {
      input->addRow(buffer);
    }
  }
  std::unique_ptr<Problem> p = input->parse();
  std::unique_ptr<Solution> s = p->solve();
  std::string message=s->toString();
  send(connfd,message.data(), message.size(),0);
}

void open(const int port){
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8087);
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  int clientfd;
  if ((clientfd = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
}