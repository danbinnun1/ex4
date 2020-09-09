#include "MatrixCreate.hpp"
#include "ProblemException.hpp"
#include <sstream>

bool is_double(std::string const &str) {
  auto result = double();
  auto i = std::istringstream(str);

  i >> result;

  return !i.fail() && i.eof();
}
bool is_number(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}
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

server_side::FindGraphPathInfo
server_side::parseMatrix(const std::vector<std::string> &rows) {
  if (rows.size() == 0) {
    throw ProblemException(NO_MATRIX_SENT);
  }
  auto matrixSizes = splitByComma(rows[0]);
  if (matrixSizes.size() != 2) {
    throw ProblemException(FIRST_LINE_DOES_NOT_REPRESENT_MATRIX_SIZE);
  }
  if (!is_number(matrixSizes[0]) || !is_number(matrixSizes[1])) {
    throw ProblemException(MATRIX_HEIGHT_AND_WIDTH_ARE_NOT_INTEGERS);
  }
  uint32_t height = std::stol(matrixSizes[0]);
  uint32_t width = std::stol(matrixSizes[0]);
  if (height == 0 || width == 0) {
    throw ProblemException(HEIGHT_OR_WIDTH_IS_ZERO);
  }
  if (rows.size() != height + 3) {
    throw ProblemException(WRONG_NUMBER_OF_ROWS);
  }
  matrix::Matrix matrix = matrix::Matrix(height, width);
  for (uint32_t i = 0; i < height; ++i) {
    auto matrixRow = splitByComma(rows[i + 3]);
    if (matrixRow.size() != width) {
      throw ProblemException(MATRIX_ROW_LENGTH_NOT_EQUAL_TO_WIDTH);
    }
    for (uint32_t j = 0; j < width; ++j) {
      if (!is_double(matrixRow[j])) {
        throw ProblemException(MATRIX_VALUE_IS_NOT_DOUBLE);
      }
      matrix.setValue(i, j, std::stod(matrixRow[j]));
    }
  }
  auto startPoint = splitByComma(rows[rows.size() - 2]);
  auto endPoint = splitByComma(rows[rows.size() - 1]);
  if (startPoint.size() != 2 || endPoint.size() != 2) {
    throw ProblemException(START_AND_END_POINTS_DO_NOT_HAVE_TWO_COORDINATES);
  }
  if (!is_number(startPoint[0]) || !is_number(startPoint[1]) ||
      !is_number(endPoint[0]) || !is_number(endPoint[1])) {
    throw ProblemException(START_AND_END_POINTS_COORDINATED_ARE_NOT_INTEGERS);
  }
  uint32_t startRow = std::stol(startPoint[0]);
  uint32_t startCol = std::stol(startPoint[1]);
  uint32_t endRow = std::stol(endPoint[0]);
  uint32_t endCol = std::stol(endPoint[1]);
  if (startCol >= width || startRow >= height || endRow >= height ||
      endCol >= width) {
    throw ProblemException(START_OR_END_POINTS_ARE_OUT_OF_THE_MATRIX);
  }
  FindGraphPathInfo info =
      FindGraphPathInfo(matrix, startRow, startCol, endRow, endCol);
  return info;
}
