#include "AStarProblem.hpp"
#include "BFSProblem.hpp"
#include "BestFSProblem.hpp"
#include "Cache.hpp"
#include "DFSProblem.hpp"
#include "ErrorCode.hpp"
#include "FindGraphPathInfo.hpp"
#include "GraphPath.hpp"
#include "ProblemException.hpp"

using namespace server_side;

std::unique_ptr<Solution> FindGraphPath::solve() const {
  uint32_t hashCode = m_info.getHash();
  if (solutionInCache(hashCode)) {
    return std::make_unique<GraphPath>(searchByHash(hashCode));
  }
  return solveProblem();
}

FindGraphPath::FindGraphPath(const FindGraphPathInfo &info) : m_info(info) {}