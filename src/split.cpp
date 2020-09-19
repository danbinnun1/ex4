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

std::vector<std::string> splitByRow(const std::string &str) {
  std::vector<std::string> rows;
  std::regex rx("[^\r\n]+\r\n");
  std::sregex_iterator FormatedFileList(str.begin(), str.end(), rx), rxend;

  while (FormatedFileList != rxend) {
    rows.push_back(FormatedFileList->str().c_str());
    ++FormatedFileList;
  }
  return rows;
}