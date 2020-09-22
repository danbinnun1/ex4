#pragma once
#include "ClientHandler.hpp"
namespace server_side{
class ProblemSolver : public ClientHandler {
private:
  
public:
  void serveClient(const int connfd) override;
};
}