#pragma once
#include <stdint.h>
namespace server_side {
class Server {
public:
  virtual void open(int port) = 0;
};
}