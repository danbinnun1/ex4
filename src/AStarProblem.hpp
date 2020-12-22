#pragma once
#include "FindGraphPath.hpp"
#include "FindGraphPathInfo.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class AStarProblem : public FindGraphPath {

public:
  //returns the path from the beginning to the target
  std::unique_ptr<Solution> solveProblem() const override;
  //returns the algorithm's name
  std::string algorithmName() const override;
  //constructor
  AStarProblem(const FindGraphPathInfo &info);
};
} // namespace server_side