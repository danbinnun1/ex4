#pragma once
#include "matrix/Matrix.hpp"
#include "GraphElement.hpp"
#include "Solution.hpp"
namespace server_side {
class FindGraphPathInfo {
private:
  matrix::Matrix m_matrix;
  uint32_t m_startRow;
  uint32_t m_startCol;
  uint32_t m_endRow;
  uint32_t m_endCol;

public:
  FindGraphPathInfo(matrix::Matrix matrix, uint32_t startRow, uint32_t startCol,
                    uint32_t endRow, uint32_t endCol);
  matrix::Matrix getMatrix() const;
  uint32_t getStartRow() const;
  uint32_t getStartCol() const;
  uint32_t getEndRow() const;
  uint32_t getEndCol() const;
  uint32_t getHash() const;
};
} // namespace server_side