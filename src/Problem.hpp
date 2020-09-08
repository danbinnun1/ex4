#pragma once
#include <Solution.hpp>
namespace server_side {
class Problem {
public:
  virtual Solution solve() const = 0;
};
}