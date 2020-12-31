#pragma once
#include <string>
#include <vector>

class Utils {
public:
	static std::vector<std::string> split(std::string str, std::string token);
	static bool strToBool(std::string str);
};

