#pragma once
#include "FindGraphPathInfo.hpp"
#include "Problem.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class FindGraphPath : public Problem {
protected:
  FindGraphPathInfo m_info;

public:
  FindGraphPath(const FindGraphPathInfo& info);
  virtual ~FindGraphPath() = default;
  std::unique_ptr<Solution> solve() const override;
  virtual std::unique_ptr<Solution> solveProblem() const = 0;
  virtual std::string algorithmName() const = 0;
};
} // namespace server_side