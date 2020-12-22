#include "DFSProblem.hpp"
#include "ErrorCode.hpp"
#include "GraphElement.hpp"
#include "GraphPath.hpp"
#include "GraphPathService.hpp"
#include "ProblemException.hpp"
#include "matrix/Matrix.hpp"
#include <stack>

std::unique_ptr<server_side::Solution>
server_side::DFSProblem::solveProblem() const {
  //creates a matrix to keep track of the graph elements we already visited
  matrix::Matrix visited = matrix::Matrix(m_info.getMatrix().getHeight(),
                                          m_info.getMatrix().getWidth());
  //creates a stack that holds the paths
  std::stack<GraphPathService> stack;
  //marks the starting graph element as visited and pushes it into the stack
  visited.setValue(m_info.getStartRow(), m_info.getStartCol(), 1);
  stack.push(GraphPathService());

  //loops over the entire stack
  while (!stack.empty()) {
    //removes the top path from the stack
    GraphPathService path = stack.top();
    stack.pop();

    //gets the graph element that the path leads to
    GraphElement s = path.applyPath(m_info);

    //checks if the path leads to the target element and returns it if it does
    if (s.getRow() == m_info.getEndRow() && s.getCol() == m_info.getEndCol()) {
      return std::make_unique<GraphPath>("DFS", path.getPath(),
                                         path.getPathWeight());
    }
    //adds the variation of the path into the queue if it is possible and the path doesn't lead to a visited node
    if (s.getRow() != 0) {
      if (visited(s.getRow() - 1, s.getCol()) != 1) {
        double weight = m_info.getMatrix()(s.getRow() - 1, s.getCol());
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow() - 1, s.getCol(), 1);
        //checks if it is possible to pass through the graph element and adds it to the stack if it is
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::up, weight);
          stack.push(newPath);
        }
      }
    }
    if (s.getCol() != 0) {
      if (visited(s.getRow(), s.getCol() - 1 != 1)) {
        double weight = m_info.getMatrix()(s.getRow(), s.getCol() - 1);
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow(), s.getCol() - 1, 1);
        //checks if it is possible to pass through the graph element and adds it to the stack if it is
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::left, weight);
          stack.push(newPath);
        }
      }
    }
    if (s.getRow() != m_info.getMatrix().getHeight() - 1) {
      if (visited(s.getRow() + 1, s.getCol()) != 1) {
        double weight = m_info.getMatrix()(s.getRow() + 1, s.getCol());
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow() + 1, s.getCol(), 1);
        //checks if it is possible to pass through the graph element and adds it to the stack if it is
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::down, weight);
          stack.push(newPath);
        }
      }
    }
    if (s.getCol() != m_info.getMatrix().getWidth() - 1) {
      if (visited(s.getRow(), s.getCol() + 1) != 1) {
        double weight = m_info.getMatrix()(s.getRow(), s.getCol() + 1);
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow(), s.getCol() + 1, 1);
        //checks if it is possible to pass through the graph element and adds it to the stack if it is
        if (weight != -1) {
          GraphPathService newPath(path);
          newPath.addDirection(Direction::right, weight);
          stack.push(newPath);
        }
      }
    }
  }

  // If DFS is complete without visiting target
  throw ProblemException(ErrorCode::NO_PATH);
}
server_side::DFSProblem::DFSProblem(const FindGraphPathInfo &info)
    : FindGraphPath(info) {}
std::string server_side::DFSProblem::algorithmName() const { return "DFS"; }