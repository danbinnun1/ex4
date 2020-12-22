#include "ProblemInput.hpp"
#include "AStarProblem.hpp"
#include "BFSProblem.hpp"
#include "BestFSProblem.hpp"
#include "DFSProblem.hpp"
#include "ErrorCode.hpp"
#include "FindGraphPathInfo.hpp"
#include "MatrixCreate.hpp"
#include "ProblemException.hpp"
#include "split.hpp"
#include <regex>

server_side::ProblemInput::ProblemInput(std::string problemRequest) {
  transform(problemRequest.begin(), problemRequest.end(),
            problemRequest.begin(), ::tolower);

  std::vector<std::string> requestWords = {};
  std::regex rgx("\\s+");
  std::sregex_token_iterator iter(problemRequest.begin(), problemRequest.end(),
                                  rgx, -1);
  std::sregex_token_iterator end;
  for (; iter != end; ++iter) {
    requestWords.push_back(*iter);
  }
  if (requestWords.size() < 2) {
    throw ProblemException(LESS_THAN_TWO_ARGUEMENTS_IN_REQUEST);
  }
  if (requestWords[0] != "solve") {
    throw ProblemException(FIRST_REQUEST_WORD_IS_NOT_SOLVE);
  }
  m_problem = requestWords[1];
  if (m_problem != "find-graph-path") {
    throw ProblemException(INVALID_PROBLEM_NAME);
  }
  if (requestWords.size() == 2) {
    m_algorithm = "bfs";
  } else {
    m_algorithm = requestWords[2];
    if (m_algorithm != "dfs" && m_algorithm != "bfs" &&
        m_algorithm != "bestfs" && m_algorithm != "a*") {
      throw ProblemException(INVALID_ALGORITHM_NAME);
    }
    if (requestWords.size() > 3) {
      throw ProblemException(MORE_THAN_THREE_REQUEST_ARGUEMENTS);
    }
  }
}

void server_side::ProblemInput::addRow(const std::string &row) {
  m_input += row;
}

std::unique_ptr<server_side::Problem> server_side::ProblemInput::parse() const {

  auto rows = splitByRow(m_input);
  FindGraphPathInfo info = parseMatrix(rows);

  if (m_algorithm == "a*") {
    return std::make_unique<AStarProblem>(info);
  }
  if (m_algorithm == "dfs") {
    return std::make_unique<DFSProblem>(info);
  }
  if (m_algorithm == "bfs") {
    return std::make_unique<BFSProblem>(info);
  } else {
    return std::make_unique<BestFSProblem>(info);
  }
}