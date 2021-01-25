#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <boost/date_time.hpp>

class Utils {
public:
	static std::vector<std::string> split(std::string str, std::string token);
	static bool strToBool(std::string str);
	static std::string boolToStr(bool value);
	static std::string implode(std::vector<std::string> vector, std::string delimiter);
	static std::string dateAsString(int dayOffset = 0);
	static bool isEmptyFile(std::fstream& file);
};

