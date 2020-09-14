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
    matrix::Matrix visited = matrix::Matrix(info.getMatrix().getHeight() , info.getMatrix().getWidth());
    std::stack<GraphPathService> stack;
    visited.setValue(info.getStartCol(), info.getStartRow(), 1); 
    stack.push(GraphPathService()); 
  
    while (!stack.empty()) 
    { 
        GraphPathService path = stack.top(); 
        stack.pop(); 

        GraphElement s = path.applyPath(info);
        
        if(s.getRow() == info.getEndRow() && s.getCol() == info.getEndCol()){
            return std::make_unique<GraphPath>("DFS", path.getPath(), path.getPathWeight());
        }
        if(s.getRow() != 0){
            if(visited(s.getCol(), s.getRow() - 1) != 1){
                double weight = info.getMatrix()(s.getCol(), s.getRow() - 1);
                visited.setValue(s.getCol(), s.getRow() - 1, 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::up, weight);
                    stack.push(newPath);
                }
            }
        }
        if(s.getCol() != 0){
            if(visited(s.getCol() - 1, s.getRow()) != 1){
                double weight = info.getMatrix()(s.getCol() - 1, s.getRow());
                visited.setValue(s.getCol() - 1, s.getRow(), 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::left, weight);
                    stack.push(newPath);
                }
            }
        }
        if(s.getRow() != info.getMatrix().getHeight() - 1){
            if(visited(s.getCol(), s.getRow() + 1) != 1){
                double weight = info.getMatrix()(s.getCol(), s.getRow() + 1);
                visited.setValue(s.getCol(), s.getRow() + 1, 1);
                if(weight != -1){
                    GraphPathService newPath(path);
                    newPath.addDirection(Direction::down, weight);
                    stack.push(newPath);
                }
            }
        }
        if(s.getRow() != info.getMatrix().getWidth() - 1){
            if(visited(s.getCol() + 1, s.getRow()) != 1){
                double weight = info.getMatrix()(s.getCol() + 1, s.getRow());
                visited.setValue(s.getCol() + 1, s.getRow(), 1);
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