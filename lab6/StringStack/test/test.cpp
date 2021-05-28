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
			THEN("stack size = 0")
			{
				REQUIRE(stack.Size() == 0);
			}

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
		CStringStack stack;
		stack.Push("test");

		WHEN("pop")
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

TEST_CASE("check functional of 'push'")
{
	GIVEN("stack without strings")
	{
		CStringStack stack;

		WHEN("push 0 strings")
		{
			THEN("size = 0; stack is empty")
			{
				REQUIRE(stack.IsEmpty());
				REQUIRE(stack.Size() == 0);
			}
		}

		WHEN("push 1 strings")
		{
			stack.Push("first");

			THEN("size = 1; is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
				REQUIRE(stack.Size() == 1);
			}
		}

		WHEN("push 2 strings")
		{
			stack.Push("first");
			stack.Push("second");

			THEN("size = 2; is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
				REQUIRE(stack.Size() == 2);
			}
		}
	}

	GIVEN("stack 1 string")
	{
		CStringStack stack;
		stack.Push("first");

		WHEN("push 0 strings")
		{
			THEN("size = 1; stack is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
				REQUIRE(stack.Size() == 1);
			}

			THEN("stack pop == 'first'")
			{
				REQUIRE(stack.Pop() == "first");
				REQUIRE(stack.IsEmpty());
			}
		}

		WHEN("push 1 strings")
		{
			stack.Push("second");

			THEN("size = 2; is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
				REQUIRE(stack.Size() == 2);
			}

			THEN("stack pop == 'second' and 'first'")
			{
				REQUIRE(stack.Pop() == "second");
				REQUIRE(stack.Pop() == "first");
				REQUIRE(stack.IsEmpty());
			}
		}

		WHEN("push 2 strings")
		{
			stack.Push("second");
			stack.Push("third");

			THEN("size = 3; is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
				REQUIRE(stack.Size() == 3);
			}

			THEN("stack pop == 'third', 'second' and 'first'")
			{
				REQUIRE(stack.Pop() == "third");
				REQUIRE(stack.Pop() == "second");
				REQUIRE(stack.Pop() == "first");
				REQUIRE(stack.IsEmpty());
			}
		}
	}
}