#pragma once
#include "FindGraphPathInfo.hpp"
#include "FindGraphPath.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class AStarProblem : public FindGraphPath {

public:
  std::unique_ptr<Solution> solveProblem() const override;
  AStarProblem(const FindGraphPathInfo& info);
};
} // namespace server_side