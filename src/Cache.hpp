#pragma once
#include <string>
namespace server_side{
 void createCache();
 bool cacheExists();
 std::string searchByHash(const std::string& inputHash);
 void insert (const std::string& hash, const std::string& result);
 bool solutionInCache(const std::string& hash);
}