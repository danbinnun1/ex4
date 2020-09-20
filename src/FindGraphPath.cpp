#include "AStarProblem.hpp"
#include "BFSProblem.hpp"
#include "BestFSProblem.hpp"
#include "Cache.hpp"
#include "DFSProblem.hpp"
#include "ErrorCode.hpp"
#include "FindGraphPathInfo.hpp"
#include "GraphPath.hpp"
#include "ProblemException.hpp"
#include <iostream>

using namespace server_side;

std::unique_ptr<Solution> FindGraphPath::solve() const {
  if(!cacheExists()){
    createCache();
  }
  uint32_t hashCode = m_info.getHash();
  if (solutionInCache(algorithmName()+ std::to_string(hashCode))) {
    return std::make_unique<GraphPath>(searchByHash(algorithmName()+ std::to_string(hashCode)));
    std::cout<<"test"<<std::endl;
  }
  std::unique_ptr<Solution> solution = solveProblem();
  insert(algorithmName()+ std::to_string(hashCode), solution.get()->toString());
  return solution;
}

FindGraphPath::FindGraphPath(const FindGraphPathInfo &info) : m_info(info) {}