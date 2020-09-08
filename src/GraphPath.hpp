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

public:
  GraphPath(const std::string &algorithm, const std::vector<Direction> &path);
  std::string toString() const override;
};

}