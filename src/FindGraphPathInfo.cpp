#include "FindGraphPath.hpp"
#include "GraphElement.hpp"
#include "Solution.hpp"
#include "Direction.hpp"
#include "GraphPathService.hpp"

using namespace server_side;

FindGraphPathInfo::FindGraphPathInfo(matrix::Matrix matrix,
                                                  uint32_t startRow,
                                                  uint32_t startCol,
                                                  uint32_t endRow,
                                                  uint32_t endCol)
    : m_matrix(matrix), m_startRow(startRow), m_startCol(startCol),
      m_endRow(endRow), m_endCol(endCol){}

uint32_t FindGraphPathInfo::getHashCode() const{
  //will be changed to an actual calculation of hashcode later
  return 5;
}



