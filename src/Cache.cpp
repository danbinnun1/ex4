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

bool server_side::cacheExists() {
  struct stat buffer;
  return stat("cache", &buffer) != -1 && S_ISDIR(buffer.st_mode);
}

std::string server_side::searchByHash(const std::string& inputHash) {
  return readFileContent("cache/"+inputHash);
}
bool server_side::solutionInCache(const std::string& inputHash) {
  
  std::ifstream infile("cache/"+inputHash);
  return infile.good();
}
void server_side::insert(const std::string& inputHash, const std::string &result) {
  writeFileContent("cache/"+inputHash,result);
}