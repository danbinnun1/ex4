#pragma once
#include "FindGraphPathInfo.hpp"
#include "FindGraphPath.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class BestFSProblem : public FindGraphPath {

public:
  std::unique_ptr<Solution> solveProblem() const override;
  BestFSProblem(const FindGraphPathInfo& info);
};
} // namespace server_side