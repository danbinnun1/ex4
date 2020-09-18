#include "AStarProblem.hpp"
#include "ErrorCode.hpp"
#include "ProblemException.hpp"
#include "matrix/Matrix.hpp"
#include <queue>
#include "GraphElement.hpp"
#include "GraphPathService.hpp"
#include "GraphPath.hpp"
using namespace server_side;

std::unique_ptr<Solution> AStarProblem::solveProblem() const{

    matrix::Matrix visited = matrix::Matrix(m_info.getMatrix().getHeight() , m_info.getMatrix().getWidth());
    std::priority_queue<GraphPathService, std::vector<GraphPathService>, LargerThanByPathWeight> queue;
    visited.setValue(m_info.getStartRow(), m_info.getStartCol(), 1); 
    queue.push(GraphPathService()); 
  
    while (!queue.empty()) 
    { 
        GraphPathService path = queue.top(); 
        queue.pop(); 

        GraphElement s = path.applyPath(m_info);
        
        if(s.getRow() == m_info.getEndRow() && s.getCol() == m_info.getEndCol()){
            return std::make_unique<GraphPath>("A*", path.getPath(), path.getPathWeight());
        }
        if(s.getRow() != 0){
            if(visited(s.getRow() - 1, s.getCol()) != 1){
                double weight = m_info.getMatrix()(s.getRow() - 1, s.getCol());
                visited.setValue(s.getRow() - 1, s.getCol(), 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::up, weight);
                    queue.push(newPath);
                }
            }
        }
        if(s.getCol() != 0){
            if(visited(s.getRow(), s.getCol() - 1 != 1)){
                double weight = m_info.getMatrix()(s.getRow(), s.getCol() - 1);
                visited.setValue(s.getRow(), s.getCol() - 1, 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::left, weight);
                    queue.push(newPath);
                }
            }
        }
        if(s.getRow() != m_info.getMatrix().getHeight() - 1){
            if(visited(s.getRow() + 1, s.getCol()) != 1){
                double weight = m_info.getMatrix()(s.getRow() + 1, s.getCol());
                visited.setValue(s.getRow() + 1, s.getCol(), 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::down, weight);
                    queue.push(newPath);
                }
            }
        }
        if(s.getCol() != m_info.getMatrix().getWidth() - 1){
            if(visited(s.getRow(), s.getCol() + 1) != 1){
                double weight = m_info.getMatrix()(s.getRow(), s.getCol() + 1);
                visited.setValue(s.getRow(), s.getCol() + 1, 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::right, weight);
                    queue.push(newPath);
                }
            }
        }
    } 
      
    // If A* is complete without visiting target 
    throw ProblemException(ErrorCode::NO_PATH);
}

AStarProblem::AStarProblem(const FindGraphPathInfo& info) :FindGraphPath(info){}