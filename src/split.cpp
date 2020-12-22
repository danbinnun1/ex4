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

std::vector<std::string> splitByRow(std::string str) {
  str+="\r\n";
  std::vector<std::string> rows;
  size_t pos = 0;
  std::string token;
  std::string delimiter="\r\n";
  while ((pos = str.find(delimiter)) != std::string::npos) {
    token = str.substr(0, pos);
    rows.push_back(token);
    str.erase(0, (pos + delimiter.length()));
  }
  return rows;
}