#pragma once
#include "ClientHandler.hpp"
namespace server_side{
class ProblemSolver : public ClientHandler {
public:
  //serves client by its connection's file descriptor
  void serveClient(const int connfd) override;
};
}