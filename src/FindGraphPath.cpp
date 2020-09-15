#include "ErrorCode.hpp"
#include "ProblemException.hpp"
#include "FindGraphPathInfo.hpp"
#include "BestFSProblem.hpp"
#include "BFSProblem.hpp"
#include "DFSProblem.hpp"
#include "AStarProblem.hpp"
#include "Cache.hpp"
#include "GraphPath.hpp"

using namespace server_side;

std::unique_ptr<Solution> FindGraphPath::solve() const {
    uint32_t hashCode = info.getHash();
    if(solutionInCache(hashCode)){
        return std::make_unique<GraphPath>(searchByHash(hashCode));
    }
    return solveProblem();
}


