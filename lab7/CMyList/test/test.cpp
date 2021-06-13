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

		WHEN("push front with insert front 2 element")
		{
			list.Insert(list.begin(), 1);
			list.Insert(list.begin(), 2);

			THEN("size = 2")
			{
				REQUIRE(list.Size() == 2);
			}

			THEN("list is not empty")
			{
				REQUIRE_FALSE(list.IsEmpty());
			}
		}

		WHEN("push front and after first")
		{
			list.Insert(list.begin(), 1);
			list.Insert(list.begin()++, 2);

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

TEST_CASE("test of getting elements")
{
	GIVEN("list with 0 elements")
	{
		CMyList<int> list;

		WHEN("pop front")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.PopFront());
				REQUIRE_THROWS_AS(list.PopFront(), UnableGetElementError);
			}
		}

		WHEN("pop back")
		{
			THEN("exception")
			{
				REQUIRE_THROWS(list.PopBack());
				REQUIRE_THROWS_AS(list.PopBack(), UnableGetElementError);
			}
		}
	}

	GIVEN("list with 1 elements")
	{
		CMyList<int> list;
		list.PushFront(1);

		WHEN("pop front")
		{
			int element = list.PopFront();

			THEN("element = 1")
			{
				REQUIRE(element == 1);
				REQUIRE(list.Size() == 1);
			}
		}

		WHEN("pop back")
		{
			int element = list.PopBack();

			THEN("element = 1")
			{
				REQUIRE(element == 1);
				REQUIRE(list.Size() == 1);
			}
		}

		WHEN("const pop front")
		{
			const int element = list.PopFront();

			THEN("element = 1")
			{
				REQUIRE(element == 1);

				REQUIRE(list.Size() == 1);
			}
		}

		WHEN("const pop back")
		{
			const int element = list.PopBack();

			THEN("element = 1")
			{
				REQUIRE(element == 1);

				REQUIRE(list.Size() == 1);
			}
		}
	}

	GIVEN("list with 2 elements")
	{
		CMyList<int> list;
		list.PushFront(1);
		list.PushFront(2);

		WHEN("pop front")
		{
			int element = list.PopFront();

			THEN("element = 2")
			{
				REQUIRE(element == 2);
				REQUIRE(list.Size() == 2);
			}
		}

		WHEN("pop back")
		{
			int element = list.PopBack();

			THEN("element = 1")
			{
				REQUIRE(element == 1);
				REQUIRE(list.Size() == 2);
			}
		}

		WHEN("const pop front")
		{
			const int element = list.PopFront();

			THEN("element = 2")
			{
				REQUIRE(element == 2);

				REQUIRE(list.Size() == 2);
			}
		}

		WHEN("const pop back")
		{
			const int element = list.PopBack();

			THEN("element = 1")
			{
				REQUIRE(element == 1);

				REQUIRE(list.Size() == 2);
			}
		}
	}
}