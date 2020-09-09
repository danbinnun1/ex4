#pragma once
#include "FindGraphPathInfo.hpp"
#include "matrix/Matrix.hpp"
#include <memory>
#include <string>
#include <vector>
namespace server_side {
FindGraphPathInfo parseMatrix(const std::vector<std::string> &rows);
}