#include "Utils.h"

#include <algorithm>

using namespace std;

string Utils::removeCharsFromString(string str, const char* charsToRemove) {
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
	}

	return str;
}

std::string Utils::removeLeadingSpaces(const std::string & str)
{
	size_t leadingSpacesCount = 0;
	while (leadingSpacesCount < str.length() && str[leadingSpacesCount] == ' ') {
		leadingSpacesCount++;
	}
	return str.substr(leadingSpacesCount);
}