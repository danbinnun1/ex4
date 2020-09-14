#include "GraphPathService.hpp"
#include "Direction.hpp"
#include <vector>

using namespace server_side;

server_side::GraphPathService::GraphPathService()
    : m_path(std::vector<Direction>()), m_pathWeight(0), m_lastWeight(0) {}

void GraphPathService::addDirection(Direction d, double weight){
    m_path.push_back(d);
    m_pathWeight += weight;
    m_lastWeight = weight;
}

std::vector<Direction> GraphPathService::getPath() const{
    return m_path;
}

double GraphPathService::getPathWeight() const{
    return m_pathWeight;
}

double GraphPathService::getLastWeight() const{
    return m_lastWeight;
}

GraphElement GraphPathService::applyPath(FindGraphPathInfo info){
  uint32_t row = info.getStartRow();
  uint32_t col = info.getStartCol();
  for(Direction d : m_path){
    if(d == Direction::up){
      row--;
    }
    else if(d == Direction::down){
      row++;
    }
    else if(d == Direction::left){
      col--;
    }
    else if(d == Direction::right){
      col++;
    }
  }
  return GraphElement(row, col);
}

bool LargerThanByLastWeight::operator()(const GraphPathService& lhs, const GraphPathService& rhs) const
{
  return lhs.getPathWeight() > rhs.getPathWeight();
}

bool LargerThanByLastWeight::operator()(const GraphPathService& lhs, const GraphPathService& rhs) const
{
  return lhs.getLastWeight() > rhs.getLastWeight();
}

