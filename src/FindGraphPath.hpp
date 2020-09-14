#pragma once
#include "FindGraphPathInfo.hpp"
#include "Problem.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class FindGraphPath : public Problem {
protected:
  FindGraphPathInfo info;

public:
  FindGraphPath(const Matrix matrix, const uint32_t startRow,
                const uint32_t startCol, const uint32_t endRow,
                const uint32_t endCol);
  virtual ~FindGraphPath() = default;
  std::unique_ptr<Solution> solve() const override;
  virtual std::unique_ptr<Solution> solveProblem() const = 0;

};
} // namespace server_side