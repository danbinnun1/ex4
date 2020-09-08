#pragma once
#include "Problem.hpp"
#include <string>
#include <vector>
namespace server_side {
class ProblemInput {
private:
  std::vector<std::string> m_inputRows;

public:
  ProblemInput(const std::string& problemRequest);
  Problem parse() const;
  void addRow(const std::string& row);
};
}