#pragma once
#include "Solution.hpp"
#include <memory>
namespace server_side {
class Problem {
public:
  virtual std::unique_ptr<Solution> solve() const = 0;
  virtual ~Problem()=default;
};
}