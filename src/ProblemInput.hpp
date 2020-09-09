#pragma once
#include "Problem.hpp"
#include <string>
#include <vector>
namespace server_side {
class ProblemInput {
private:
  std::vector<std::string> m_inputRows;
  std::string m_problem;
  std::string m_algorithm;

public:
  ProblemInput(const std::string &problemRequest);
  std::unique_ptr<Problem> parse() const;
  void addRow(const std::string &row);
};
} // namespace server_side