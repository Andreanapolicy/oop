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

TEST_CASE("check functional of push")
{
	GIVEN("list with size 0 type of int")
	{
		CMyList<int> list;

		WHEN("push 0 element")
		{
			THEN("size = 0")
			{
				REQUIRE(list.Size() == 0);
			}

			THEN("list is empty")
			{
				REQUIRE(list.IsEmpty());
			}
		}
		
		WHEN("push front 1 element")
		{
			list.PushFront(1);

			THEN("size = 1")
			{
				REQUIRE(list.Size() == 1);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push front 2 element")
		{
			list.PushFront(1);
			list.PushFront(2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push back 1 element")
		{
			list.PushBack(1);

			THEN("size = 1")
			{
				REQUIRE(list.Size() == 1);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push back 2 element")
		{
			list.PushBack(1);
			list.PushBack(2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push back with push front 2 element")
		{
			list.PushBack(1);
			list.PushFront(2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}
	}
}