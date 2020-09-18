#include "DFSProblem.hpp"
#include "ErrorCode.hpp"
#include "ProblemException.hpp"
#include "matrix/Matrix.hpp"
#include "GraphElement.hpp"
#include "GraphPathService.hpp"
#include <stack>
#include "GraphPath.hpp"

using namespace server_side;

std::unique_ptr<Solution> DFSProblem::solveProblem() const{
    matrix::Matrix visited = matrix::Matrix(m_info.getMatrix().getHeight() , m_info.getMatrix().getWidth());
    std::stack<GraphPathService> stack;
    visited.setValue(m_info.getStartRow(), m_info.getStartCol(), 1); 
    stack.push(GraphPathService()); 
  
    while (!stack.empty()) 
    { 
        GraphPathService path = stack.top(); 
        stack.pop(); 

        GraphElement s = path.applyPath(m_info);
        
        if(s.getRow() == m_info.getEndRow() && s.getCol() == m_info.getEndCol()){
            return std::make_unique<GraphPath>("DFS", path.getPath(), path.getPathWeight());
        }
        if(s.getRow() != 0){
            if(visited(s.getRow() - 1, s.getCol()) != 1){
                double weight = m_info.getMatrix()(s.getRow() - 1, s.getCol());
                visited.setValue(s.getRow() - 1, s.getCol(), 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::up, weight);
                    stack.push(newPath);
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
                    stack.push(newPath);
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
                    stack.push(newPath);
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
                    stack.push(newPath);
                }
            }
        }
    } 
      
    // If DFS is complete without visiting target 
    throw ProblemException(ErrorCode::NO_PATH);
}
DFSProblem::DFSProblem(const FindGraphPathInfo& info): FindGraphPath(info){}