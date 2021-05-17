#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../StringStack/CStringStack.h"
#include "../StringStack/CEmptyStackError.h"

TEST_CASE("check functional of 'pop'")
{
	GIVEN("stack without strings")
	{
		CStringStack stack;

		WHEN("pop stack")
		{
			THEN("exception: Empty Stack")
			{
				REQUIRE_THROWS(stack.Pop());
				REQUIRE_THROWS_AS(stack.Pop(), CEmptyStackError);
			}
		}

		WHEN("check is empty stack")
		{
			THEN("stack is empty")
			{
				REQUIRE(stack.IsEmpty());
			}
		}
	}

	GIVEN("stack with 1 string 'test'")
	{
		CStringStack stack("test");

		WHEN("pop stack")
		{
			THEN("without exception")
			{
				REQUIRE_NOTHROW(stack.Pop());
			}

			THEN("string = 'test'. After pop stack is empty")
			{
				REQUIRE(stack.Pop() == "test");
				REQUIRE(stack.IsEmpty());		
			}

			THEN("string = 'test'. After another one pop will be exception")
			{
				REQUIRE(stack.Pop() == "test");
				REQUIRE_THROWS(stack.Pop());
				REQUIRE_THROWS_AS(stack.Pop(), CEmptyStackError);
			}
		}
	}
}