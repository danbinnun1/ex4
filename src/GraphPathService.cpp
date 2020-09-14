#include "GraphPathService.hpp"
#include "Direction.hpp"
#include <vector>


server_side::GraphPathService::GraphPathService()
    : m_path(std::vector<Direction>()), m_pathWeight(0), m_lastWeight(0) {}

void server_side::GraphPathService::addDirection(Direction d, double weight){
    m_path.push_back(d);
    m_pathWeight += weight;
    m_lastWeight = weight;
}

std::vector<server_side::Direction> server_side::GraphPathService::getPath() const{
    return m_path;
}

double server_side::GraphPathService::getPathWeight() const{
    return m_pathWeight;
}

double server_side::GraphPathService::getLastWeight() const{
    return m_lastWeight;
}

server_side::GraphElement server_side::GraphPathService::applyPath(server_side::FindGraphPathInfo info){
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

bool server_side::LargerThanByLastWeight::operator()(const GraphPathService& lhs, const GraphPathService& rhs) const
{
  return lhs.getPathWeight() > rhs.getPathWeight();
}

bool server_side::LargerThanByLastWeight::operator()(const GraphPathService& lhs, const GraphPathService& rhs) const
{
  return lhs.getLastWeight() > rhs.getLastWeight();
}

