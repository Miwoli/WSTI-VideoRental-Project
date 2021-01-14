#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

class Utils {
public:
	static std::vector<std::string> split(std::string str, std::string token);
	static bool strToBool(std::string str);
	static std::string boolToStr(bool value);
	static std::string implode(std::vector<std::string> vector, std::string delimiter);
	static std::string nowAsString();
};

