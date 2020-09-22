#pragma once
#include <stdint.h>
#include <memory>
#include "ClientHandler.hpp"
namespace server_side {
class Server {
public:
  virtual void open(const int port, std::unique_ptr<ClientHandler> handler) = 0;
  virtual ~Server() = default;
};
} // namespace server_side