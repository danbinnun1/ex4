#pragma once
#include "Direction.hpp"
#include "Solution.hpp"
#include <memory>
#include <string>
#include <vector>
#include "FindGraphPathInfo.hpp"
#include "GraphElement.hpp"
namespace server_side {
class GraphPathService {
private:
  std::vector<Direction> m_path;
  double m_pathWeight;
  double m_lastWeight;

public:
  GraphPathService();
  void addDirection(Direction d, double weight);
  std::vector<Direction> getPath() const;
  double getPathWeight() const;
  double getLastWeight() const;
  GraphElement applyPath(const FindGraphPathInfo& info);
};

struct LargerThanByPathWeight
{
  bool operator()(const GraphPathService& lhs, const GraphPathService& rhs) const;
};

struct LargerThanByLastWeight
{
  bool operator()(const GraphPathService& lhs, const GraphPathService& rhs) const;
};
}