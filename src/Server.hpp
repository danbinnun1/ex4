#pragma once
#include <stdint.h>
namespace server_side {
class Server {
public:
  virtual void open(const int port) = 0;
  virtual ~Server() = default;
};
} // namespace server_side