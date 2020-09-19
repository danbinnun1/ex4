#pragma once
#include <string>
namespace server_side{
 void createCache();
 bool cacheExists();
 std::string searchByHash(const uint32_t inputHash);
 void insert (const uint32_t hash, const std::string& result);
 bool solutionInCache(const uint32_t hash);
}