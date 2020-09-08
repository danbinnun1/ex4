#pragma once
#include <stdint.h>
namespace server_side {
class Server {
public:
  virtual void open(int port, uint32_t maxClients) = 0;
};
}