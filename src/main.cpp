#include "Cache.hpp"
#include "ReaderServer.hpp"
#include <iostream>
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
  if (argc > 3 || argc < 2) {
    std::cerr << "wrong number of arguements" << std::endl;
    return -1;
  }
  if (!is_int(argv[1])) {
    std::cerr << "invalid port" << std::endl;
    return -1;
  }
  int port = std::stol(argv[1]);
  if (argc == 2) {
    server_side::ReaderServer server("\r\n", 50, 5000);
    server.open(port);
  } else {
    if (strcmp(argv[2], "serial") == 0) {
      server_side::ReaderServer server("\r\n", 1, 5000);
      server.open(port);
    } else if (strcmp(argv[2], "parallel") == 0) {
      server_side::ReaderServer server("\r\n", 50, 5000);
      server.open(port);
    } else {
      std::cerr << "invalid server type parameter" << std::endl;
      return -1;
    }
  }
  return 0;
}
