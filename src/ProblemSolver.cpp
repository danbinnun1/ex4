#include "ProblemSolver.hpp"
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
#include <string>
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

void timer(const long waitTime, bool &finished, bool &timeoutPassed) {
  long start = duration_cast<milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
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
  while (read(connfd, buffer, 1024) == 0)
    ;
  finished = true;
}
void readMessageWithTimeout(int connfd, char *buffer, bool &recievedMessage,
                            long waitTime) {
  bool finished = false;
  bool timeoutPassed = false;
  std::thread readClinetMessage(readMessage, std::ref(finished), connfd,
                                buffer);
  timer(waitTime, std::ref(finished), std::ref(timeoutPassed));
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
void server_side::ProblemSolver::serveClient(const int connfd) {
  try {
    char buffer[1024] = {0};
    bool recievedMessage;
    readMessageWithTimeout(connfd, buffer, recievedMessage, 5000);
    if (!recievedMessage) {
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
      readMessageWithTimeout(connfd, buffer, recievedMessage, 5000);
      if (!recievedMessage) {
        return;
      }
      std::string row = std::string(buffer);

      std::string enter = "\r\n";
      if (ends_with(row, enter + enter)) {
        std::string h = row.substr(0, row.size() - enter.size() - enter.size());
        input->addRow(h);
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
}