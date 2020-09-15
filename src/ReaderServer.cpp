#include "ReaderServer.hpp"
#include "ProblemInput.hpp"
#include <boost/thread.hpp>
#include <cstring>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <threads.h>
#include <unistd.h>
server_side::ReaderServer::ReaderServer(const std::string &end,
                                        uint32_t maxClients, long waitTime)
    : m_end(end), m_maxClients(maxClients), m_waitTime(waitTime),
      m_currentClients(0) {}

void server_side::ReaderServer::serveClient(const int connfd,
                                            const std::string &problem,
                                            const std::string &alg) {
  char buffer[1024] = {0};
  boost::thread readRequest(read, connfd, buffer, sizeof(buffer));
  if (readRequest.timed_join(
          boost::posix_time::milliseconds(m_waitTime))) // wait for 1s
  {
    std::unique_ptr<ProblemInput> input =
        std::make_unique<ProblemInput>(buffer);
    bool clientFinished = false;
    while (!clientFinished) {
      memset(buffer, 0, sizeof(buffer));
      boost::thread readClientMessage(read, connfd, buffer, sizeof(buffer));
      if (readClientMessage.timed_join(
              boost::posix_time::milliseconds(m_waitTime))) {
        if (buffer == m_end) {
          clientFinished = true;
        } else {
          input->addRow(buffer);
        }
      } else {
        close(connfd);
        return;
      }
    }
    std::unique_ptr<Problem> p=input->parse();
    std::unique_ptr<Solution> s=p->solve();
  } else {
    // throw std::runtime_error("timeout");
    //std::cout << "g" << std::endl;
  }
  read(connfd, buffer, sizeof(buffer));
}