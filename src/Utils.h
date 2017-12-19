#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
	std::string removeCharsFromString(std::string str, const char* charsToRemove);
	std::string trim(const std::string& str, const std::string& whitespace = " \t");
	std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");
	bool isDigits(const std::string &str);
}

#endif