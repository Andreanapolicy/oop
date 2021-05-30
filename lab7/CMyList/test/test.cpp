#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyList/CMyList.h"

TEST_CASE("check functional of constructors")
{
	GIVEN("list with size 0")
	{
		CMyList<int> list;

		THEN("size = 0")
		{
			REQUIRE(list.Size() == 0);
		}

		THEN("list is empty")
		{
			REQUIRE(list.IsEmpty());
		}
	}
}