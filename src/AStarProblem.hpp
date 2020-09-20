#pragma once
#include "FindGraphPath.hpp"
#include "FindGraphPathInfo.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class AStarProblem : public FindGraphPath {

public:
  std::unique_ptr<Solution> solveProblem() const override;
  std::string algorithmName() const override;
  AStarProblem(const FindGraphPathInfo &info);
};
} // namespace server_side