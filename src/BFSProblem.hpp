#pragma once
#include "FindGraphPath.hpp"
#include "FindGraphPathInfo.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class BFSProblem : public FindGraphPath {

public:
  //returns the path from the beginning to the target
  std::unique_ptr<Solution> solveProblem() const override;
  //returns the algorithm's name
  BFSProblem(const FindGraphPathInfo &info);
  //constructor
  std::string algorithmName() const override;
};
} // namespace server_side