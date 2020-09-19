#include "GraphPath.hpp"
#include "Direction.hpp"
#include <regex>
#include "split.hpp"
#include <string.h>

server_side::GraphPath::GraphPath(const std::string &algorithm,
                                  const std::vector<Direction> &path,
                                  double pathWeight)
    : m_path(path), m_algorithm(algorithm), m_pathWeight(pathWeight) {}
std::string server_side::GraphPath::toString() const {
  std::string s = "";
  s += std::to_string(m_pathWeight);
  s += ",";
  s += m_algorithm;
  for (auto const &direction : m_path) {
    s += ",";
    if (direction == Direction::up) {
      s += "Up";
    } else if (direction == Direction::down) {
      s += "Down";
    } else if (direction == Direction::left) {
      s += "Left";
    } else {
      s += "Right";
    }
  }
  return s;
}

server_side::GraphPath::GraphPath(std::string s){
    auto parts=splitByComma(s);
    m_pathWeight=std::stod(parts[0]);
    m_algorithm=parts[1];
    m_path=std::vector<Direction>();
    for (uint32_t i=0;i<parts.size();++i){
        if (parts[i]=="Up"){
            m_path.push_back(Direction::up);
        }
        if (parts[i]=="Down"){
            m_path.push_back(Direction::down);
        }
        if (parts[i]=="Right"){
            m_path.push_back(Direction::right);
        }
        if (parts[i]=="Left"){
            m_path.push_back(Direction::left);
        }
    }
}