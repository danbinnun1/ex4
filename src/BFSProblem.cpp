#include "BFSProblem.hpp"
#include "ErrorCode.hpp"
#include "GraphElement.hpp"
#include "GraphPath.hpp"
#include "GraphPathService.hpp"
#include "ProblemException.hpp"
#include "matrix/Matrix.hpp"
#include <list>

std::unique_ptr<server_side::Solution>
server_side::BFSProblem::solveProblem() const {
  //creates a matrix to keep track of the graph elements we already visited
  matrix::Matrix visited = matrix::Matrix(m_info.getMatrix().getHeight(),
                                          m_info.getMatrix().getWidth());
  //creates a queue that holds the paths
  std::list<GraphPathService> queue;
  //marks the starting graph element as visited and pushes it into the queue
  visited.setValue(m_info.getStartRow(), m_info.getStartCol(), 1);
  queue.push_back(GraphPathService());

  //loops over the entire queue
  while (!queue.empty()) {
    //removes the top path from the queue
    GraphPathService path = queue.front();
    queue.pop_front();

    //gets the graph element that the path leads to
    GraphElement s = path.applyPath(m_info);

    //checks if the path leads to the target element and returns it if it does
    if (s.getRow() == m_info.getEndRow() && s.getCol() == m_info.getEndCol()) {
      return std::make_unique<GraphPath>("BFS", path.getPath(),
                                         path.getPathWeight());
    }
    //adds the variation of the path into the queue if it is possible and the path doesn't lead to a visited node
    if (s.getRow() != 0) {
      if (visited(s.getRow() - 1, s.getCol()) != 1) {
        double weight = m_info.getMatrix()(s.getRow() - 1, s.getCol());
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow() - 1, s.getCol(), 1);
        //checks if it is possible to pass through the graph element and adds it to the queue if it is
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
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow(), s.getCol() - 1, 1);
        //checks if it is possible to pass through the graph element and adds it to the queue if it is
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
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow() + 1, s.getCol(), 1);
        //checks if it is possible to pass through the graph element and adds it to the queue if it is
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
        //marks the graph element which the new path leads to as visited
        visited.setValue(s.getRow(), s.getCol() + 1, 1);
        //checks if it is possible to pass through the graph element and adds it to the queue if it is
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

server_side::BFSProblem::BFSProblem(const FindGraphPathInfo &info)
    : FindGraphPath(info) {}
std::string server_side::BFSProblem::algorithmName() const { return "BFS"; }