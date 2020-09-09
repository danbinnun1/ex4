#pragma once
#include "FindGraphPathInfo.hpp"
#include "Problem.hpp"
#include "matrix/Matrix.hpp"
namespace server_side {
class FindGraphPath : public Problem {
private:
  FindGraphPathInfo info;

public:
  FindGraphPath(const Matrix matrix, const uint32_t startRow,
                const uint32_t startCol, const uint32_t endRow,
                const uint32_t endCol);
  virtual ~FindGraphPath() = default;
};
} // namespace server_side