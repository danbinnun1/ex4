#pragma once
#include "FindGraphPathInfo.hpp"
#include "FindGraphPath.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class BFSProblem : public FindGraphPath {

public:
  std::unique_ptr<Solution> solveProblem() const override;
  BFSProblem(const FindGraphPathInfo& info);
    std::string algorithmName() const override;

};
} // namespace server_side