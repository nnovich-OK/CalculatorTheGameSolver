#include "Utils.h"

#include <algorithm>

using namespace std;

string Utils::removeCharsFromString(string str, const char* charsToRemove) {
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
	}

	return str;
}