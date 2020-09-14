#include "split.hpp"
#include <regex>

std::vector<std::string> splitByComma(const std::string &str) {
  std::vector<std::string> result;
  std::stringstream s_stream(str); // create string stream from the string
  while (s_stream.good()) {
    std::string substr;
    std::getline(s_stream, substr, ','); // get first string delimited by comma
    result.push_back(substr);
  }
  return result;
}