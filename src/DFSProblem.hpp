#pragma once
#include "FindGraphPathInfo.hpp"
#include "FindGraphPath.hpp"
#include "matrix/Matrix.hpp"

namespace server_side {
class DFSProblem : public FindGraphPath {

public:
  std::unique_ptr<Solution> solveProblem() const override;
  DFSProblem(const FindGraphPathInfo& info);
};
} // namespace server_side