#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Rational/common_libs.h"
#include "../Rational/CRational.h"

TEST_CASE("Test functional of getter and setter")
{
	GIVEN("rational number without value")
	{
		CRational number;
		double numberInDoubleNotation = 0;

		THEN("numerator = 0 and denominator = 1")
		{
			REQUIRE(number.GetNumerator() == 0);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number with only numerator (1)")
	{
		CRational number(1);
		double numberInDoubleNotation = 1;

		THEN("numerator = 1 and denominator = 1")
		{
			REQUIRE(number.GetNumerator() == 1);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (4/3)")
	{
		CRational number(4, 3);
		double numberInDoubleNotation = 4 / 3;

		THEN("numerator = 4 and denominator = 3")
		{
			REQUIRE(number.GetNumerator() == 4);
			REQUIRE(number.GetDenominator() == 3);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (4/0)")
	{
		int asd = 1;
		CRational number(asd);
		THEN("error, invalid params")
		{
			REQUIRE_THROWS(CRational(4, 0));
		}
	}

	GIVEN("rational number (-4/3)")
	{
		CRational number(-4, 3);
		double numberInDoubleNotation = -4 / 3;

		THEN("numerator = -4 and denominator = 3")
		{
			REQUIRE(number.GetNumerator() == -4);
			REQUIRE(number.GetDenominator() == 3);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (4/-3)")
	{
		CRational number(4, -3);
		double numberInDoubleNotation = -4 / 3;

		THEN("numerator = -4 and denominator = 3")
		{
			REQUIRE(number.GetNumerator() == -4);
			REQUIRE(number.GetDenominator() == 3);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test Euclid's algorithm")
{
	GIVEN("numbers 4 and 7")
	{
		int GCD = GetGreatestCommonDivisor(4, 7);
		THEN("gcd == 1")
		{
			REQUIRE(GCD == 1);
		}
	}

	GIVEN("numbers 4 and 2")
	{
		int GCD = GetGreatestCommonDivisor(4, 2);
		THEN("gcd == 2")
		{
			REQUIRE(GCD == 2);
		}
	}

	GIVEN("numbers 2 and 4")
	{
		int GCD = GetGreatestCommonDivisor(2, 4);
		THEN("gcd == 2")
		{
			REQUIRE(GCD == 2);
		}
	}

	GIVEN("numbers 0 and 13")
	{
		int GCD = GetGreatestCommonDivisor(0, 13);
		THEN("gcd == 13")
		{
			REQUIRE(GCD == 13);
		}
	}

	GIVEN("numbers 13 and 0")
	{
		int GCD = GetGreatestCommonDivisor(13, 0);
		THEN("gcd == 13")
		{
			REQUIRE(GCD == 13);
		}
	}

	GIVEN("numbers 0 and 0")
	{
		THEN("throw exception: 'There is no GCD for numbers (0; 0)'")
		{
			REQUIRE_THROWS(GetGreatestCommonDivisor(0, 0));
		}
	}

	GIVEN("numbers 6 and -12")
	{
		int GCD = GetGreatestCommonDivisor(6, -12);
		THEN("gcd == 6")
		{
			REQUIRE(GCD == 6);
		}
	}
}

TEST_CASE("Test functional of normalize")
{
	GIVEN("rational number (4/2)")
	{
		CRational number(4, 2);
		double numberInDoubleNotation = 2;

		THEN("normalize fraction is (2/1)")
		{
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (-4/2)")
	{
		CRational number(-4, 2);
		double numberInDoubleNotation = -2;

		THEN("normalize fraction is (-2/1)")
		{
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational number (13/11)")
	{
		CRational number(13, 11);
		double numberInDoubleNotation = 13 / 11;

		THEN("normalize fraction is (13/11)")
		{
			REQUIRE(number.GetNumerator() == 13);
			REQUIRE(number.GetDenominator() == 11);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test functional unary + and -")
{
	GIVEN("rational number (4/2)")
	{
		CRational number(4, 2);
		double numberInDoubleNotation = 2;

		THEN("fraction is (2/1) with unary +")
		{
			number = +number;
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}

		THEN("fraction is (-2/1) with unary -")
		{
			number = -number;
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == -numberInDoubleNotation);
		}
	}

	GIVEN("rational number (-4/2)")
	{
		CRational number(-4, 2);
		double numberInDoubleNotation = -2;

		THEN("fraction is (2/1) with unary -")
		{
			number = -number;
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == -numberInDoubleNotation);
		}

		THEN("fraction is (-2/1) with unary +")
		{
			number = +number;
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test functional input and output")
{
	GIVEN("rational number (4/2) in input")
	{
		std::istringstream iss("4/2");
		std::ostringstream oss;
		CRational number;
		double numberInDoubleNotation = 2;

		iss >> number;

		THEN("fraction is (2/1)")
		{
			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);

		}

		THEN("fraction (2/1) in output")
		{
			oss << number;
			REQUIRE(oss.str() == "2/1");

			REQUIRE(number.GetNumerator() == 2);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);

		}
	}
}

TEST_CASE("Test functional binary + and - (with and without assign)")
{
	GIVEN("rational numbers (1/3) and (1/2)")
	{
		CRational number1(1, 3);
		CRational number2(1, 2);
		
		THEN("(1/3) + (1/2) = (5/6)")
		{
			double numberInDoubleNotation = 5 / 6;

			CRational resultNumber = number1 + number2;
			REQUIRE(resultNumber.GetNumerator() == 5);
			REQUIRE(resultNumber.GetDenominator() == 6);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) - (1/2) = (-1/3)")
		{
			double numberInDoubleNotation = -1 / 6;

			CRational resultNumber = number1 - number2;
			REQUIRE(resultNumber.GetNumerator() == -1);
			REQUIRE(resultNumber.GetDenominator() == 6);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) + (1/2) = (5/6) with assign")
		{
			double numberInDoubleNotation = 5 / 6;

			number1 += number2;
			REQUIRE(number1.GetNumerator() == 5);
			REQUIRE(number1.GetDenominator() == 6);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) - (1/2) = (-1/3) with assign")
		{
			double numberInDoubleNotation = -1 / 6;

			number1 -= number2;
			REQUIRE(number1.GetNumerator() == -1);
			REQUIRE(number1.GetDenominator() == 6);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and (3/6)")
	{
		CRational number1(2, 4);
		CRational number2(3, 6);

		THEN("(2/4) + (3/6) = (1/1)")
		{
			double numberInDoubleNotation = 1;
			
			CRational resultNumber = number1 + number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) - (3/6) = (0/1)")
		{
			double numberInDoubleNotation = 0;
			
			CRational resultNumber = number1 - number2;
			REQUIRE(resultNumber.GetNumerator() == 0);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and 2")
	{
		CRational number(2, 4);

		THEN("(2/4) + 2 = (5/2)")
		{
			double numberInDoubleNotation = 5 / 2;
			
			CRational resultNumber = number + 2;
			REQUIRE(resultNumber.GetNumerator() == 5);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) - 2 = (-3/2)")
		{
			double numberInDoubleNotation = -3 / 2;
			
			CRational resultNumber = number - 2;
			REQUIRE(resultNumber.GetNumerator() == -3);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers 2 and (2/4)")
	{
		CRational number(2, 4);

		THEN("2 + (2/4) = (5/2)")
		{
			double numberInDoubleNotation = 5 / 2;

			CRational resultNumber = 2 + number;
			REQUIRE(resultNumber.GetNumerator() == 5);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("2 - (2/4) = (3/2)")
		{
			double numberInDoubleNotation = 3 / 2;

			CRational resultNumber = 2 - number;
			REQUIRE(resultNumber.GetNumerator() == 3);
			REQUIRE(resultNumber.GetDenominator() == 2);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) + 2 = (5/2) with assign")
		{
			double numberInDoubleNotation = 5 / 2;

			number += 2;
			REQUIRE(number.GetNumerator() == 5);
			REQUIRE(number.GetDenominator() == 2);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) - 2 = (-3/2) with assign")
		{
			double numberInDoubleNotation = -3 / 2;

			number -= 2;
			REQUIRE(number.GetNumerator() == -3);
			REQUIRE(number.GetDenominator() == 2);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}
}

TEST_CASE("Test functional binary / and * (with and without assign)")
{
	GIVEN("rational numbers (1/3) and (1/2)")
	{
		CRational number1(1, 3);
		CRational number2(1, 2);

		THEN("(1/3) * (1/2) = (1/6)")
		{
			double numberInDoubleNotation = 1 / 6;

			CRational resultNumber = number1 * number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 6);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) / (1/2) = (2/3)")
		{
			double numberInDoubleNotation = 2 / 3;

			CRational resultNumber = number1 / number2;
			REQUIRE(resultNumber.GetNumerator() == 2);
			REQUIRE(resultNumber.GetDenominator() == 3);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) * (1/2) = (1/6) with assign")
		{
			double numberInDoubleNotation = 1 / 6;

			number1 *= number2;
			REQUIRE(number1.GetNumerator() == 1);
			REQUIRE(number1.GetDenominator() == 6);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}

		THEN("(1/3) / (1/2) = (2/3) with assign")
		{
			double numberInDoubleNotation = 2 / 3;

			number1 /= number2;
			REQUIRE(number1.GetNumerator() == 2);
			REQUIRE(number1.GetDenominator() == 3);
			REQUIRE(number1.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and (3/6)")
	{
		CRational number1(2, 4);
		CRational number2(3, 6);

		THEN("(2/4) * (3/6) = (1/4)")
		{
			double numberInDoubleNotation = 1 / 4;

			CRational resultNumber = number1 * number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 4);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / (3/6) = (1)")
		{
			double numberInDoubleNotation = 1;

			CRational resultNumber = number1 / number2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and 2")
	{
		CRational number(2, 4);

		THEN("(2/4) * 2 = (1)")
		{
			double numberInDoubleNotation = 1;

			CRational resultNumber = number * 2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / 2 = (1/4)")
		{
			double numberInDoubleNotation = 1 / 4;

			CRational resultNumber = number / 2;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 4);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers 2 and (2/4)")
	{
		CRational number(2, 4);

		THEN("2 * (2/4) = (1)")
		{
			double numberInDoubleNotation = 1;

			CRational resultNumber = 2 * number;
			REQUIRE(resultNumber.GetNumerator() == 1);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("2 / (2/4) = (4)")
		{
			double numberInDoubleNotation = 4;

			CRational resultNumber = 2 / number;
			REQUIRE(resultNumber.GetNumerator() == 4);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) * 2 = (1) with assign")
		{
			double numberInDoubleNotation = 1;

			number *= 2;
			REQUIRE(number.GetNumerator() == 1);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / 2 = (1/4) with assign")
		{
			double numberInDoubleNotation = 1 / 4;

			number /= 2;
			REQUIRE(number.GetNumerator() == 1);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == numberInDoubleNotation);
		}
	}

	GIVEN("rational numbers (2/4) and 0")
	{
		CRational number(2, 4);

		THEN("(2/4) * 0 = (0)")
		{
			double numberInDoubleNotation = 0;

			CRational resultNumber = number * 0;
			REQUIRE(resultNumber.GetNumerator() == 0);
			REQUIRE(resultNumber.GetDenominator() == 1);
			REQUIRE(resultNumber.ToDouble() == numberInDoubleNotation);
		}

		THEN("(2/4) / 0 = exception: Error while dividing on 0")
		{
			REQUIRE_THROWS(number / 0);
		}
	}
}