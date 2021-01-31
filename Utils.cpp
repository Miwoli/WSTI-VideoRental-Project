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

std::string Utils::dateAsString(int dayOffset) {
    boost::posix_time::ptime timelocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date dateObj = timelocal.date();
    boost::posix_time::time_duration timeDuration = timelocal.time_of_day();

    boost::posix_time::ptime timeUTC = boost::posix_time::second_clock::universal_time();
    boost::posix_time::hours offset(dayOffset * 24);

    return boost::posix_time::to_iso_extended_string(timeUTC + offset);
}

bool Utils::isEmptyFile(std::fstream& file) {
    return file.peek() == std::fstream::traits_type::eof();
}
