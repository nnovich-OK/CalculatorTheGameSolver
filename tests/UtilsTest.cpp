#include "Utils.h"
#include "gtest/gtest.h"

using namespace std;
using namespace Utils;

TEST(UtilsTest, removeCharsFromString) {
	const string testString = "a_bb ccc";
	const string emptyString;

	//remove one char
	EXPECT_EQ(removeCharsFromString(testString, "a"), string("_bb ccc"));

	//remove multiple chars
	EXPECT_EQ(removeCharsFromString(testString, "c_"), string("abb "));

	//remove non-existing char
	EXPECT_EQ(removeCharsFromString(testString, "z"), testString);

	//remove nothing
	EXPECT_EQ(removeCharsFromString(testString, ""), testString);

	//remove anything from empty string
	EXPECT_EQ(removeCharsFromString(emptyString, "abc "), emptyString);
}

TEST(UtilsTest, trim) {
	const string testString = " \t  some  \t string   \t ";
	const string emptyString;

	//usual trim
	EXPECT_EQ(trim(testString), string("some  \t string"));

	//space only trim
	EXPECT_EQ(trim(testString, " "), string("\t  some  \t string   \t"));

	//empty trim
	EXPECT_EQ(trim(testString, ""), testString);

	//empty string
	EXPECT_EQ(trim(emptyString), emptyString);
}

TEST(UtilsTest, reduce) {
	const string testString = " \t  some  \t string   \t ";
	const string emptyString;

	//usual reduce
	EXPECT_EQ(reduce(testString), string("some string"));

	//different fill
	EXPECT_EQ(reduce(testString, "\t"), string("some\tstring"));

	//space only reduce
	EXPECT_EQ(reduce(testString, " ", " "), string("\t some \t string \t"));

	//empty reduce
	EXPECT_EQ(reduce(testString, " ", ""), testString);

	//empty string
	EXPECT_EQ(reduce(emptyString), emptyString);
}

TEST(UtilsTest, isDigits) {
	//simple number
	EXPECT_TRUE(isDigits("1"));

	//duplicate digits
	EXPECT_TRUE(isDigits("111"));

	//all digits
	EXPECT_TRUE(isDigits("1234567890"));

	//letter
	EXPECT_FALSE(isDigits("1a"));

	//space
	EXPECT_FALSE(isDigits(" 1"));

	//not sure what empty string should return, so commented out
	//EXPECT_TRUE(isDigits(""));
}