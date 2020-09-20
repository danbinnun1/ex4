#include "BFSProblem.hpp"
#include "ErrorCode.hpp"
#include "GraphElement.hpp"
#include "GraphPath.hpp"
#include "GraphPathService.hpp"
#include "ProblemException.hpp"
#include "matrix/Matrix.hpp"
#include <list>
using namespace server_side;

std::unique_ptr<Solution> BFSProblem::solveProblem() const {
  matrix::Matrix visited = matrix::Matrix(m_info.getMatrix().getHeight(),
                                          m_info.getMatrix().getWidth());
  std::list<GraphPathService> queue;
  visited.setValue(m_info.getStartRow(), m_info.getStartCol(), 1);
  queue.push_back(GraphPathService());

  while (!queue.empty()) {
    GraphPathService path = queue.front();
    queue.pop_front();

    GraphElement s = path.applyPath(m_info);

    if (s.getRow() == m_info.getEndRow() && s.getCol() == m_info.getEndCol()) {
      return std::make_unique<GraphPath>("BFS", path.getPath(),
                                         path.getPathWeight());
    }
    if (s.getRow() != 0) {
      if (visited(s.getRow() - 1, s.getCol()) != 1) {
        double weight = m_info.getMatrix()(s.getRow() - 1, s.getCol());
        visited.setValue(s.getRow() - 1, s.getCol(), 1);
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::up, weight);
          queue.push_back(newPath);
        }
      }
    }
    if (s.getCol() != 0) {
      if (visited(s.getRow(), s.getCol() - 1 != 1)) {
        double weight = m_info.getMatrix()(s.getRow(), s.getCol() - 1);
        visited.setValue(s.getRow(), s.getCol() - 1, 1);
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::left, weight);
          queue.push_back(newPath);
        }
      }
    }
    if (s.getRow() != m_info.getMatrix().getHeight() - 1) {
      if (visited(s.getRow() + 1, s.getCol()) != 1) {
        double weight = m_info.getMatrix()(s.getRow() + 1, s.getCol());
        visited.setValue(s.getRow() + 1, s.getCol(), 1);
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::down, weight);
          queue.push_back(newPath);
        }
      }
    }
    if (s.getCol() != m_info.getMatrix().getWidth() - 1) {
      if (visited(s.getRow(), s.getCol() + 1) != 1) {
        double weight = m_info.getMatrix()(s.getRow(), s.getCol() + 1);
        visited.setValue(s.getRow(), s.getCol() + 1, 1);
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::right, weight);
          queue.push_back(newPath);
        }
      }
    }
  }

  // If BFS is complete without visiting target
  throw ProblemException(ErrorCode::NO_PATH);
}

BFSProblem::BFSProblem(const FindGraphPathInfo &info) : FindGraphPath(info) {}
std::string BFSProblem::algorithmName() const { return "BFS"; }