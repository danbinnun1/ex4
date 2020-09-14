#include "GraphPath.hpp"
#include "Direction.hpp"

server_side::GraphPath::GraphPath(const std::string &algorithm,
                                  const std::vector<Direction> &path,
                                  double pathWeight)
    : m_path(path), m_algorithm(algorithm), m_pathWeight(pathWeight) {}
std::string server_side::GraphPath::toString() const {
  std::string s = "";
  s += m_pathWeight;
  s+=",";
  s+=m_algorithm;
  for (auto const& direction:m_path){
      s+=",";
      if (direction==Direction::up){
          s+="Up";
      }
      else if (direction==Direction::down){
          s+="Down";
      }
      else if (direction==Direction::left){
          s+="Left";
      }
      else{
          s+="Right";
      }
  }
  return s;
}

server_side::GraphPath::GraphPath(std::string s){

}
