#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CCalculator.h"
#include "../common_libs.h"

TEST_CASE("Incorrect name of variable")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		WHEN("create new var with value 1 and with name 123x")
		{
			calc.SetVarValue("123x", "1");

			THEN("value of new var is NaN")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("123x")));
			}
		}

		WHEN("create new var with value 1 and with name _123x")
		{
			calc.SetVarValue("_123x", "1");

			THEN("value of new var is 1")
			{
				REQUIRE(calc.GetIdentifierValue("_123x") == 1);
			}
		}
	}
}

TEST_CASE("Creating vars with values of different vars")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		WHEN("create new var with value of var y")
		{
			calc.CreateNewVar("x");
			calc.SetVarValue("y", "1");

			calc.SetVarValue("x", "y");

			THEN("value of new var is NaN")
			{
				REQUIRE(calc.GetIdentifierValue("x") == 1);
				REQUIRE(calc.GetIdentifierValue("y") == 1);
				REQUIRE(calc.GetAllVars().size() == 2);
				REQUIRE(calc.GetAllVars() == std::map<std::string, double>{ { "x", 1 }, { "y", 1 } });
			}
		}

		WHEN("create var y with value of var x(NaN)")
		{
			calc.CreateNewVar("x");
			calc.SetVarValue("y", "x");

			THEN("value of new var is NaN")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("x")));
				REQUIRE(std::isnan(calc.GetIdentifierValue("y")));
				REQUIRE(calc.GetAllVars().size() == 2);
			}
		}

		WHEN("create new var with value 1 at the same time")
		{
			calc.SetVarValue("x", "1");

			THEN("value of new var is 1")
			{
				REQUIRE(calc.GetIdentifierValue("x") == 1);

				REQUIRE(calc.GetAllVars().size() == 1);
			}
		}

		WHEN("create new var and after that give value 1")
		{
			calc.CreateNewVar("x");
			calc.SetVarValue("x", "1");
			calc.SetVarValue("y", "2");

			THEN("value of new var is 1")
			{
				REQUIRE(calc.GetIdentifierValue("x") == 1);
				REQUIRE(calc.GetIdentifierValue("y") == 2);

				REQUIRE(calc.GetAllVars().size() == 2);
				REQUIRE(calc.GetAllVars() == std::map<std::string, double>{ { "x", 1 }, { "y", 2 } });
			}
		}
	}
}

TEST_CASE("Creating vars with or without values")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		WHEN("create new var without value")
		{
			calc.CreateNewVar("x");

			THEN("value of new var is NaN")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("x")));
				REQUIRE(calc.GetAllVars().size() == 1);
			}
		}

		WHEN("create new var with value 1 at the same time")
		{
			calc.SetVarValue("x", "1");

			THEN("value of new var is 1")
			{
				REQUIRE(calc.GetIdentifierValue("x") == 1);

				REQUIRE(calc.GetAllVars().size() == 1);
			}
		}

		WHEN("create new var and after that give value 1")
		{
			calc.CreateNewVar("x");
			calc.SetVarValue("x", "1");
			calc.SetVarValue("y", "2");

			THEN("value of new var is 1")
			{
				REQUIRE(calc.GetIdentifierValue("x") == 1);
				REQUIRE(calc.GetIdentifierValue("y") == 2);

				REQUIRE(calc.GetAllVars().size() == 2);
				REQUIRE(calc.GetAllVars() == std::map<std::string, double>{ { "x", 1 }, { "y", 2 } });
			}
		}
	}
}

TEST_CASE("Creating functions")
{
	GIVEN("A calculator")
	{
		CCalculator calc;

		WHEN("create new function fn = x and fn1 = fn + x, where x = NaN")
		{
			calc.CreateNewVar("x");

			calc.SetFunctionValue(std::pair<std::string, CCalculator::Expression>("fn", std::pair<char, std::vector<std::string>>(' ', { "x" })));
			calc.SetFunctionValue(std::pair<std::string, CCalculator::Expression>("fn1", std::pair<char, std::vector<std::string>>('+', { "x", "fn" })));

			THEN("add fn = x and fn1 = fn + x")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("x")));
				REQUIRE(calc.GetAllFunctions().size() == 2);
			}
		}
	}
}
