#include "FindGraphPath.hpp"
#include "crc32.h"
#include <bitset>
#include <functional>
server_side::FindGraphPathInfo::FindGraphPathInfo(matrix::Matrix matrix,
                                                  uint32_t startRow,
                                                  uint32_t startCol,
                                                  uint32_t endRow,
                                                  uint32_t endCol)
    : m_matrix(matrix), m_startRow(startRow), m_startCol(startCol),
      m_endRow(endRow), m_endCol(endCol) {}
uint32_t server_side::FindGraphPathInfo::getHash() const {
  std::string s = "";
  s += std::to_string(m_startRow);
  s += ",";
  s += std::to_string(m_startCol);
  s += "\n";
  s += std::to_string(m_endRow);
  s += ",";
  s += std::to_string(m_endCol);
  s += "\n";
  for (int i = 0; i < m_matrix.getHeight(); ++i) {
    for (int j = 0; j < m_matrix.getWidth(); ++j) {
      s += std::to_string(m_matrix(i, j));
      s += ",";
    }
    s += "\n";
  }
  return calculate_crc32c(0, (const unsigned char *)s.c_str(), s.size());
}
