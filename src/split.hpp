#pragma once
#include <vector>
#include <string>
//splits string by comma
std::vector<std::string> splitByComma(const std::string &str);
//split string by \r\n
std::vector<std::string> splitByRow(std::string str);