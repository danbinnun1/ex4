#pragma once
#include "Problem.hpp"
#include <string>
#include <vector>
namespace server_side {
class ProblemInput {
private:
  std::string m_input;
  std::string m_problem;
  std::string m_algorithm;

public:
  ProblemInput(std::string problemRequest);
  //parses the input and returns a problem object
  std::unique_ptr<Problem> parse() const;
  void addRow(const std::string &row);
};
} // namespace server_side