#include "ProblemInput.hpp"
#include "ErrorCode.hpp"
#include "ProblemException.hpp"
#include <regex>

server_side::ProblemInput::ProblemInput(const std::string &problemRequest) {
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
    m_algorithm = "BFS";
  } else {
    m_algorithm = requestWords[2];
    if (m_algorithm != "DFS" && m_algorithm != "DFS" &&
        m_algorithm != "BestFS" && m_algorithm != "A*") {
      throw ProblemException(INVALID_ALGORITHM_NAME);
    }
    if (requestWords.size() > 3) {
      throw ProblemException(MORE_THAN_THREE_REQUEST_ARGUEMENTS);
    }
  }
}

void server_side::ProblemInput::addRow(const std::string &row) {
  m_inputRows.push_back(row);
}

//std::unique_ptr<server_side::Problem> server_side::ProblemInput::parse() const {
//if (m_problem == "find-graph-path") {
      
//}
//}