#include "FindGraphPath.hpp"

server_side::FindGraphPathInfo::FindGraphPathInfo(matrix::Matrix matrix,
                                                  uint32_t startRow,
                                                  uint32_t startCol,
                                                  uint32_t endRow,
                                                  uint32_t endCol)
    : m_matrix(matrix), m_startRow(startRow), m_startCol(startCol),
      m_endRow(endRow), m_endCol(endCol) {}