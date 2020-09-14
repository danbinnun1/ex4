#include "Cache.hpp"
#include "file_reading.hpp"
#include <bits/stdc++.h>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/types.h>
void server_side::createCache() {
  if (mkdir("cache", 0777) == -1)
    throw std::runtime_error("could not create cache");
}

std::string server_side::searchByHash(const uint32_t inputHash) {
  return readFileContent("cache/"+std::to_string(inputHash));
}
bool server_side::solutionInCache(const uint32_t inputHash) {
  
  std::ifstream infile("cache/"+std::to_string(inputHash));
  return infile.good();
}
void server_side::insert(const uint32_t inputHash, const std::string &result) {
  writeFileContent("cache/"+std::to_string(inputHash),result);
}