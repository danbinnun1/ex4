#include "Cache.hpp"
#include "ClientHandler.hpp"
#include "ParallelServer.hpp"
#include "ProblemSolver.hpp"
#include "SerialServer.hpp"
#include "Server.hpp"
#include "ServerException.hpp"
#include <iostream>
#include <memory>
#include <string.h>

bool is_int(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}

int main(int argc, char *argv[]) {
  if (!server_side::cacheExists()) {
    server_side::createCache();
  }
  try {
    if (argc > 3 || argc < 2) {
      std::cerr << "wrong number of arguements" << std::endl;
      return -1;
    }
    if (!is_int(argv[1])) {
      std::cerr << "invalid port" << std::endl;
      return -1;
    }
    const int port = std::stol(argv[1]);
    if (argc == 2) {
      std::unique_ptr<server_side::Server> server =
          std::make_unique<server_side::ParallelServer>();
      server->open(port, std::make_unique<server_side::ProblemSolver>());
    } else {
      if (strcmp(argv[2], "serial") == 0) {
        std::unique_ptr<server_side::Server> server =
            std::make_unique<server_side::SerialServer>();
        server->open(port, std::make_unique<server_side::ProblemSolver>());
      } else if (strcmp(argv[2], "parallel") == 0) {
        std::unique_ptr<server_side::Server> server =
            std::make_unique<server_side::ParallelServer>();
        server->open(port, std::make_unique<server_side::ProblemSolver>());
      } else {
        std::cerr << "invalid server type parameter" << std::endl;
        return -1;
      }
    }
    return 0;
  } catch (const server_side::ServerException &e) {
    std::cerr << e.what() << std::endl;
  }
}
