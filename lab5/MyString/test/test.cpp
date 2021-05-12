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

	GIVEN("string '', that created by empty string")
	{
		CMyString string("");

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(string.GetLength() == 0);
			REQUIRE(string.GetStringData()[0] == '\0');
		}
	}

	GIVEN("string 'hello' with length 0")
	{
		CMyString string("hello", 0);

		THEN("lenght is 0 and string is '\0'")
		{
			REQUIRE(string.GetLength() == 0);
			REQUIRE(string.GetStringData()[0] == '\0');
		}
	}

	GIVEN("string 'hello world' with fixed length 5")
	{
		CMyString string("hello world", 5);

		THEN("lenght is 5 and string is 'hello\0'")
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

	GIVEN("string 'hello world' with fixed length -5")
	{
		THEN("exception: 'Error, length is < 0'")
		{
			REQUIRE_THROWS(CMyString("hello world", -5));
		}
	}

	GIVEN("string 'hello world', that created by copying")
	{
		CMyString string("hello world");
		CMyString copiedString = string;

		THEN("lenght is 11 and string is 'hello world\0'")
		{
			const char* resultString = copiedString.GetStringData();
			REQUIRE(copiedString.GetLength() == 11);
			REQUIRE(resultString[0] == 'h');
			REQUIRE(resultString[1] == 'e');
			REQUIRE(resultString[2] == 'l');
			REQUIRE(resultString[3] == 'l');
			REQUIRE(resultString[4] == 'o');
			REQUIRE(resultString[5] == ' ');
			REQUIRE(resultString[6] == 'w');
			REQUIRE(resultString[7] == 'o');
			REQUIRE(resultString[8] == 'r');
			REQUIRE(resultString[9] == 'l');
			REQUIRE(resultString[10] == 'd');
			REQUIRE(resultString[11] == '\0');
		}
	}

	GIVEN("string '', that created by copying")
	{
		CMyString copiedString = CMyString("");

		THEN("lenght is 0 and string is '\0'")
		{
			const char* resultString = copiedString.GetStringData();
			REQUIRE(copiedString.GetLength() == 0);
			REQUIRE(resultString[0] == '\0');
		}
	}

	GIVEN("string '', that stl string")
	{
		std::string emptyStlString = "";
		CMyString copiedString(emptyStlString);

		THEN("lenght is 0 and string is '\0'")
		{
			const char* resultString = copiedString.GetStringData();
			REQUIRE(copiedString.GetLength() == 0);
			REQUIRE(resultString[0] == '\0');
		}
	}

	GIVEN("string 'hello', that is stl string")
	{
		std::string helloStlString = "hello";
		CMyString copiedString = helloStlString;

		THEN("lenght is 5 and string is 'hello\0'")
		{
			const char* resultString = copiedString.GetStringData();
			REQUIRE(copiedString.GetLength() == 5);
			REQUIRE(resultString[0] == 'h');
			REQUIRE(resultString[1] == 'e');
			REQUIRE(resultString[2] == 'l');
			REQUIRE(resultString[3] == 'l');
			REQUIRE(resultString[4] == 'o');
		}
	}
}

TEST_CASE("Test functional of substring")
{
	GIVEN("string 'hello'")
	{
		CMyString string = "hello";

		WHEN("substring(5, 4)")
		{
			THEN("exception: 'Wrong params'")
			{
				REQUIRE_THROWS(string.GetSubString(5, 4));
			}
		}

		WHEN("substring(500, 4)")
		{
			THEN("exception: 'Wrong params'")
			{
				REQUIRE_THROWS(string.GetSubString(500, 4));
			}
		}

		WHEN("substring(4, 4)")
		{
			THEN("string: ''")
			{
				CMyString substring = string.GetSubString(4, 4);
				const char* resultString = substring.GetStringData();
				REQUIRE(string.GetSubString(4, 4).GetLength() == 0);
				REQUIRE(resultString[0] == '\0');
			}
		}

		WHEN("substring(0)")
		{
			THEN("string: 'hello'")
			{
				CMyString substring = string.GetSubString(0);
				const char* resultString = substring.GetStringData();
				REQUIRE(substring.GetLength() == 5);
				REQUIRE(resultString[0] == 'h');
				REQUIRE(resultString[1] == 'e');
				REQUIRE(resultString[2] == 'l');
				REQUIRE(resultString[3] == 'l');
				REQUIRE(resultString[4] == 'o');
				REQUIRE(resultString[5] == '\0');
			}
		}

		WHEN("substring(0, 1230)")
		{
			THEN("string: 'hello'")
			{
				CMyString substring = string.GetSubString(0, 1230);
				const char* resultString = substring.GetStringData();
				REQUIRE(substring.GetLength() == 5);
				REQUIRE(resultString[0] == 'h');
				REQUIRE(resultString[1] == 'e');
				REQUIRE(resultString[2] == 'l');
				REQUIRE(resultString[3] == 'l');
				REQUIRE(resultString[4] == 'o');
				REQUIRE(resultString[5] == '\0');
			}
		}

		WHEN("substring(0, 4)")
		{
			THEN("string: 'hell'")
			{
				CMyString substring = string.GetSubString(0, 4);
				const char* resultString = substring.GetStringData();
				REQUIRE(substring.GetLength() == 4);
				REQUIRE(resultString[0] == 'h');
				REQUIRE(resultString[1] == 'e');
				REQUIRE(resultString[2] == 'l');
				REQUIRE(resultString[3] == 'l');
				REQUIRE(resultString[4] == '\0');
			}
		}

		WHEN("substring(0, 3)")
		{
			THEN("string: 'hel'")
			{
				CMyString substring = string.GetSubString(0, 3);
				const char* resultString = substring.GetStringData();
				REQUIRE(substring.GetLength() == 3);
				REQUIRE(resultString[0] == 'h');
				REQUIRE(resultString[1] == 'e');
				REQUIRE(resultString[2] == 'l');
				REQUIRE(resultString[3] == '\0');
			}
		}

		WHEN("substring(0, 2)")
		{
			THEN("string: 'he'")
			{
				CMyString substring = string.GetSubString(0, 2);
				const char* resultString = substring.GetStringData();
				REQUIRE(substring.GetLength() == 2);
				REQUIRE(resultString[0] == 'h');
				REQUIRE(resultString[1] == 'e');
				REQUIRE(resultString[2] == '\0');
			}
		}

		WHEN("substring(1, 2)")
		{
			THEN("string: 'e'")
			{
				CMyString substring = string.GetSubString(1, 2);
				const char* resultString = substring.GetStringData();
				REQUIRE(substring.GetLength() == 1);
				REQUIRE(resultString[0] == 'e');
				REQUIRE(resultString[1] == '\0');
			}
		}
	}
}

TEST_CASE("Test functional of assign")
{
	GIVEN("s = 'hello' b = 'bonjour'")
	{
		CMyString s = "hello";
		CMyString b = "bonjour";

		WHEN("s = b")
		{
			s = b;

			THEN("s = 'bonjour'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 7);
				REQUIRE(resultString[0] == 'b');
				REQUIRE(resultString[1] == 'o');
				REQUIRE(resultString[2] == 'n');
				REQUIRE(resultString[3] == 'j');
				REQUIRE(resultString[4] == 'o');
				REQUIRE(resultString[5] == 'u');
				REQUIRE(resultString[6] == 'r');
				REQUIRE(resultString[7] == '\0');
			}

			THEN("b = 'bonjour'")
			{
				const char* startString = b.GetStringData();

				REQUIRE(startString[0] == 'b');
				REQUIRE(startString[1] == 'o');
				REQUIRE(startString[2] == 'n');
				REQUIRE(startString[3] == 'j');
				REQUIRE(startString[4] == 'o');
				REQUIRE(startString[5] == 'u');
				REQUIRE(startString[6] == 'r');
				REQUIRE(startString[7] == '\0');
			}
		}

		WHEN("b = s")
		{
			b = s;

			THEN("b = 'hello'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 5);
				REQUIRE(resultString[0] == 'h');
				REQUIRE(resultString[1] == 'e');
				REQUIRE(resultString[2] == 'l');
				REQUIRE(resultString[3] == 'l');
				REQUIRE(resultString[4] == 'o');
				REQUIRE(resultString[5] == '\0');
			}

			THEN("s = 'hello'")
			{
				const char* startString = b.GetStringData();

				REQUIRE(startString[0] == 'h');
				REQUIRE(startString[1] == 'e');
				REQUIRE(startString[2] == 'l');
				REQUIRE(startString[3] == 'l');
				REQUIRE(startString[4] == 'o');
				REQUIRE(startString[5] == '\0');
			}
		}

		WHEN("s = s")
		{
			s = s;

			THEN("s = 'hello'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 5);
				REQUIRE(resultString[0] == 'h');
				REQUIRE(resultString[1] == 'e');
				REQUIRE(resultString[2] == 'l');
				REQUIRE(resultString[3] == 'l');
				REQUIRE(resultString[4] == 'o');
				REQUIRE(resultString[5] == '\0');
			}
		}

		WHEN("s = ''")
		{
			s = "";

			THEN("s = ''")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 0);
				REQUIRE(resultString[0] == '\0');
			}
		}
	}
}

TEST_CASE("Test functional of +")
{
	GIVEN("s = 'qw' b = 'ert'")
	{
		CMyString s = "qw";
		CMyString b = "ert";

		WHEN("s = s + b")
		{
			s = s + b;

			THEN("s = 'qwert'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 5);
				REQUIRE(resultString[0] == 'q');
				REQUIRE(resultString[1] == 'w');
				REQUIRE(resultString[2] == 'e');
				REQUIRE(resultString[3] == 'r');
				REQUIRE(resultString[4] == 't');
				REQUIRE(resultString[5] == '\0');
			}
		}

		WHEN("s = '' + b")
		{
			s = "" + b;

			THEN("s = 'ert'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 3);
				REQUIRE(resultString[0] == 'e');
				REQUIRE(resultString[1] == 'r');
				REQUIRE(resultString[2] == 't');
				REQUIRE(resultString[3] == '\0');
			}
		}

		WHEN("s = b + ''")
		{
			s = b + "";

			THEN("s = 'ert'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 3);
				REQUIRE(resultString[0] == 'e');
				REQUIRE(resultString[1] == 'r');
				REQUIRE(resultString[2] == 't');
				REQUIRE(resultString[3] == '\0');
			}
		}
	}

	GIVEN("s = 'test'")
	{
		CMyString s = "test";

		WHEN("s = '1' + s")
		{
			s = "1" + s;

			THEN("s = '1test'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 5);
				REQUIRE(resultString[0] == '1');
				REQUIRE(resultString[1] == 't');
				REQUIRE(resultString[2] == 'e');
				REQUIRE(resultString[3] == 's');
				REQUIRE(resultString[4] == 't');
				REQUIRE(resultString[5] == '\0');
			}
		}

		WHEN("s = '1' + '23'")
		{
			std::string number = "1";
			s = number + "23";

			THEN("s = '123'")
			{
				const char* resultString = s.GetStringData();

				REQUIRE(s.GetLength() == 3);
				REQUIRE(resultString[0] == '1');
				REQUIRE(resultString[1] == '2');
				REQUIRE(resultString[2] == '3');
				REQUIRE(resultString[3] == '\0');
			}
		}
	}
}
