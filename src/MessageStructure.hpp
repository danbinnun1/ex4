#pragma once
#include <string>
namespace server_side{
//returns string in the default format
std::string getStructure(const uint32_t status, const std::string& response);
}