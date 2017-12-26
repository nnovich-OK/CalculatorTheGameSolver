#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {

	/** 
	Create new string based on the given one with all specified chars removed
	*/
	std::string removeCharsFromString(std::string str, const char* charsToRemove);

	/**
	Remove whitespace chars in the beginning and end of the string
	*/
	std::string trim(const std::string& str, const std::string& whitespace = " \t");

	/**
	Remove leading, trailing or consequent whitespace chars, relacing the latter with "fill" chars
	*/
	std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");

	/**
	Check if string consists of digit chars only
	*/
	bool isDigits(const std::string &str);
}

#endif