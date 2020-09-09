#pragma once
#include <string>
namespace server_side {
class Solution {
public:
  virtual std::string toString() const = 0;
  virtual ~Solution() = default;
};
} // namespace server_side