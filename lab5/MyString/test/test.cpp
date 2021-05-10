#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyString/CMyString.h"
#include "../MyString/common_libs.h"

TEST_CASE("Test functional of constructors")
{
	GIVEN("string 'hello\0'")
	{
		CMyString string("hello");

		THEN("lenght is 5 and string is 'hello'")
		{
			const char* resultString = string.GetStringData();
			REQUIRE(string.GetLength() == 5);
			REQUIRE(resultString[0] == 'h');
			REQUIRE(resultString[1] == 'e');
			REQUIRE(resultString[2] == 'l');
			REQUIRE(resultString[3] == 'l');
			REQUIRE(resultString[4] == 'o');
			REQUIRE(resultString[5] == '\0');
		}
	}

	GIVEN("string ''")
	{
		CMyString string;

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(string.GetLength() == 0);
			REQUIRE(string.GetStringData()[0] == '\0');
		}
	}
}