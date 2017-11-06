#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
	std::string removeCharsFromString(std::string str, const char* charsToRemove);
	std::string removeLeadingSpaces(const std::string& str);
}

#endif