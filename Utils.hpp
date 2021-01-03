#pragma once
#include <string>
#include <vector>

class Utils {
public:
	static std::vector<std::string> split(std::string str, std::string token);
	static bool strToBool(std::string str);
	static std::string boolToStr(bool value);
	static std::string implode(std::vector<std::string> vector, char delimiter);
};

