#include "ReaderServer.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <threads.h>
#include <unistd.h>
#include <memory>
#include <cstring> 
#include "ProblemInput.hpp"
server_side::ReaderServer::ReaderServer(const std::string &end,
                                        uint32_t maxClients,
                                        std::chrono::milliseconds waitTime)
    : m_end(end), m_maxClients(maxClients), m_waitTime(waitTime),
      m_currentClients(0) {}

void server_side::ReaderServer::serveClient(const int connfd,
                                            const std::string &problem,
                                            const std::string &alg) {
  char buffer[1024]={0};
  
      read(connfd,buffer,sizeof(buffer));
      std::unique_ptr<ProblemInput> input=std::make_unique<ProblemInput>(buffer);
      bool clientFinished=false;
      while (!clientFinished)
      {
          memset(buffer,0, sizeof(buffer));
          std::thread readClientMessage(read,connfd,buffer,sizeof(buffer));
          
          //read(connfd,buffer, sizeof(buffer));
      }
      
  
}