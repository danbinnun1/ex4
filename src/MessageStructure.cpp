#include "MessageStructure.hpp"

std::string server_side::getStructure(const uint32_t status,
                                      const std::string &response) {
  std::string s = "Version: 1.0\r\n";
  s += "status: ";
  s += std::to_string(status);
  s += "\r\n";
  s += "response-length: ";
  s += std::to_string(response.size());
  s += "\r\n\r\n";
  s += response;
  return s;
}