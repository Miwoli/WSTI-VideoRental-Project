#include "Utils.hpp"

std::vector<std::string> Utils::split(std::string str, std::string token) {
    std::vector<std::string> result;

    while (str.size()) {
        int index = str.find(token);
        if (index != std::string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0) result.push_back(str);
        } else {
            result.push_back(str);
            str = "";
        }
    }

    return result;
}

bool Utils::strToBool(std::string str) {
    return (str == "false" || str == "0") ? false : true;
}

std::string Utils::boolToStr(bool value) {
    return value ? "true" : "false";
}

std::string Utils::implode(std::vector<std::string> vector, std::string delimiter) {
    std::string result;
    for (const auto &item : vector) {
        result += item + delimiter;
    }
    result.pop_back();
    return result;
}

std::string Utils::nowAsString() {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    int day = newtime.tm_mday;
    int month = 1 + newtime.tm_mon;
    int year = 1900 + newtime.tm_year;

    return std::to_string(day) + "-" + (month < 10 ? ("0" + std::to_string(month)) : std::to_string(month)) + "-" + std::to_string(year);
}

bool Utils::isEmptyFile(std::fstream& file) {
    return file.peek() == std::fstream::traits_type::eof();
}
