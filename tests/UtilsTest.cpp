#include "Utils.h"
#include "gtest/gtest.h"

using namespace std;
using namespace Utils;

TEST(Utils, removeCharsFromString) {
	const string testString = "a_bb ccc";
	const string emptyString;

	//remove one char
	ASSERT_EQ(removeCharsFromString(testString, "a"), string("_bb ccc"));

	//remove multiple chars
	ASSERT_EQ(removeCharsFromString(testString, "c_"), string("abb "));

	//remove non-existing char
	ASSERT_EQ(removeCharsFromString(testString, "z"), testString);

	//remove nothing
	ASSERT_EQ(removeCharsFromString(testString, ""), testString);

	//remove anything from empty string
	ASSERT_EQ(removeCharsFromString(emptyString, "abc "), emptyString);
}

TEST(Utils, trim) {
	const string testString = " \t  some  \t string   \t ";
	const string emptyString;

	//usual trim
	ASSERT_EQ(trim(testString), string("some  \t string"));

	//space only trim
	ASSERT_EQ(trim(testString, " "), string("\t  some  \t string   \t"));

	//empty trim
	ASSERT_EQ(trim(testString, ""), testString);

	//empty string
	ASSERT_EQ(trim(emptyString), emptyString);
}

TEST(Utils, reduce) {
	const string testString = " \t  some  \t string   \t ";
	const string emptyString;

	//usual reduce
	ASSERT_EQ(reduce(testString), string("some string"));

	//different fill
	ASSERT_EQ(reduce(testString, "\t"), string("some\tstring"));

	//space only reduce
	ASSERT_EQ(reduce(testString, " ", " "), string("\t some \t string \t"));

	//empty reduce
	ASSERT_EQ(reduce(testString, " ", ""), testString);

	//empty string
	ASSERT_EQ(reduce(emptyString), emptyString);
}

TEST(Utils, isDigits) {
	//simple number
	ASSERT_TRUE(isDigits("1"));

	//duplicate digits
	ASSERT_TRUE(isDigits("111"));

	//all digits
	ASSERT_TRUE(isDigits("1234567890"));

	//letter
	ASSERT_FALSE(isDigits("1a"));

	//space
	ASSERT_FALSE(isDigits(" 1"));

	//not sure what empty string should return, so commented out
	//ASSERT_TRUE(isDigits(""));
}