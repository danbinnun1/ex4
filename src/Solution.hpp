#pragma once
#include <string>
namespace server_side {
class Solution {
public:
  //creates string from the solution in order to send to the client
  virtual std::string toString() const = 0;
  virtual ~Solution() = default;
};
} // namespace server_side