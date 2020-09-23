#pragma once
#include "Direction.hpp"
#include "Solution.hpp"
#include <memory>
#include <string>
#include <vector>
namespace server_side {
class GraphPath : public Solution {
private:
  std::vector<Direction> m_path;
  std::string m_algorithm;
  double m_pathWeight;

public:
  GraphPath(std::string algorithm, std::vector<Direction> path, double pathWeight);
  std::string toString() const override;
  GraphPath(const std::string& s);
};
}