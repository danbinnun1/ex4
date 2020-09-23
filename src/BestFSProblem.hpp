#pragma once
#include "FindGraphPath.hpp"
#include "FindGraphPathInfo.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class BestFSProblem : public FindGraphPath {

public:
  std::unique_ptr<Solution> solveProblem() const override;
  BestFSProblem(const FindGraphPathInfo &info);
  std::string algorithmName() const override;
};
} // namespace server_side