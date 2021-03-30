#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../common_libs.h"
#include "../CCar.h"

TEST_CASE("Test get info on car level")
{
	CCar car;
	REQUIRE(car.IsEngineTurn() == false);
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);

	car.TurnOnEngine();
	REQUIRE(car.IsEngineTurn() == true);
	car.TurnOffEngine();
	REQUIRE(car.IsEngineTurn() == false);
}

TEST_CASE("Test gear on wrong value")
{
	CCar car;
	car.TurnOnEngine();

	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.SetGear(-2) == false);
	REQUIRE(car.SetGear(6) == false);
	REQUIRE(car.GetGear() == 0);
}

TEST_CASE("Test speed on negative numbers")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);

	REQUIRE(car.SetSpeed(-1) == true);
	REQUIRE(car.GetSpeed() == 1);

	REQUIRE(car.SetSpeed(-50) == false);
	REQUIRE(car.GetSpeed() == 1);
}

TEST_CASE("Test car on gear 0")
{
	CCar car;
	car.TurnOnEngine();

	SECTION("Test car on gear 0 with 0 speed")
	{
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.SetSpeed(12) == false);
		REQUIRE(car.SetGear(0) == true);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetDirection() == Direction::ON_THE_SPOT);
	}

	SECTION("Test car on transition from 0 to -1 gear")
	{
		car.SetGear(-1);
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Direction::ON_THE_SPOT);
	}

	SECTION("Test car on transition from 0 to 1 gear")
	{
		car.SetGear(0);
		car.SetGear(1);
		car.SetSpeed(12);
		REQUIRE(car.GetGear() == 1);
		REQUIRE(car.GetSpeed() == 12);
		REQUIRE(car.GetDirection() == Direction::FORWARD);
	}

	SECTION("Test car on decrease speed on 0 gear")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(0);

		REQUIRE(car.GetSpeed() == 20);
		car.SetSpeed(11);
		REQUIRE(car.GetSpeed() == 11);
		REQUIRE(car.SetSpeed(13) == false);
	}
}

TEST_CASE("Test car on gear -1")
{
	CCar car;
	car.TurnOnEngine();

	SECTION("Test car on gear -1 with 0 speed")
	{
		car.SetGear(-1);
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Direction::ON_THE_SPOT);
	}

	SECTION("Test car on gear -1 with limit speed")
	{
		car.SetGear(-1);
		REQUIRE(car.SetSpeed(30) == false);
		car.SetSpeed(20);
		REQUIRE(car.GetSpeed() == 20);
		REQUIRE(car.GetDirection() == Direction::BACKWARD);
	}

	SECTION("Test car on transition from gear -1 to gear 1")
	{
		car.SetGear(-1);
		car.SetSpeed(20);

		REQUIRE(car.SetGear(1) == false);
		REQUIRE(car.GetGear() == -1);
		car.SetSpeed(0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.SetGear(1) == true);
		REQUIRE(car.GetGear() == 1);
	}

	SECTION("Test car on transition from gear -1 to gear 0")
	{
		car.SetGear(-1);
		car.SetSpeed(15);
		REQUIRE(car.SetGear(0) == true);
		REQUIRE(car.SetSpeed(17) == false);
		REQUIRE(car.SetGear(1) == false);
		car.SetSpeed(0);
		REQUIRE(car.SetGear(1) == true);
		REQUIRE(car.GetGear() == 1);
	}
}

TEST_CASE("Test car on gear 1")
{
	CCar car;
	car.TurnOnEngine();

	SECTION("Test car on gear 1 with 0 speed")
	{
		car.SetGear(1);
		REQUIRE(car.GetGear() == 1);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Direction::ON_THE_SPOT);
	}

	SECTION("Test car on gear 1 with limit speed")
	{
		car.SetGear(1);
		REQUIRE(car.SetSpeed(40) == false);
		car.SetSpeed(30);
		REQUIRE(car.GetSpeed() == 30);
		REQUIRE(car.GetDirection() == Direction::FORWARD);
		car.SetSpeed(0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Direction::ON_THE_SPOT);
	}

	SECTION("Test car on transition gears")
	{
		car.SetGear(1);
		car.SetSpeed(30);

		REQUIRE(car.SetGear(2) == true);
		REQUIRE(car.GetGear() == 2);
		
		REQUIRE(car.SetGear(3) == true);
		REQUIRE(car.GetGear() == 3);
		
		car.SetGear(1);
		car.SetSpeed(15);
		REQUIRE(car.SetGear(-1) == false);
		REQUIRE(car.SetGear(1) == true);
		REQUIRE(car.GetGear() == 1);
	}

	SECTION("Test car on transition from gear -1 to gear 0")
	{
		car.SetGear(-1);
		car.SetSpeed(15);
		REQUIRE(car.SetGear(0) == true);
		REQUIRE(car.SetSpeed(17) == false);
		REQUIRE(car.SetGear(1) == false);
		car.SetSpeed(0);
		REQUIRE(car.SetGear(1) == true);
		REQUIRE(car.GetGear() == 1);
	}
}

TEST_CASE("Test car on gear upper than 1")
{
	CCar car;
	car.TurnOnEngine();

	SECTION("Test car on gear 1 with limit speed")
	{
		car.SetGear(1);
		REQUIRE(car.SetSpeed(30) == true);
		REQUIRE(car.SetGear(2) == true);
		REQUIRE(car.SetSpeed(50) == true);
		REQUIRE(car.SetGear(3) == true);
		REQUIRE(car.SetSpeed(60) == true);
		REQUIRE(car.SetGear(4) == true);
		REQUIRE(car.SetSpeed(90) == true);
		REQUIRE(car.SetGear(5) == true);
		REQUIRE(car.SetSpeed(150) == true);
		REQUIRE(car.SetSpeed(151) == false);
		REQUIRE(car.SetGear(6) == false);
		REQUIRE(car.SetSpeed(49) == false);

		REQUIRE(car.SetSpeed(50) == true);

		REQUIRE(car.SetGear(4) == true);
		REQUIRE(car.SetSpeed(91) == false);
		REQUIRE(car.SetSpeed(39) == false);

		REQUIRE(car.SetSpeed(40) == true);

		REQUIRE(car.SetGear(3) == true);
		REQUIRE(car.SetSpeed(61) == false);
		REQUIRE(car.SetSpeed(29) == false);

		REQUIRE(car.SetSpeed(30) == true);

		REQUIRE(car.SetGear(2) == true);
		REQUIRE(car.SetSpeed(51) == false);
		REQUIRE(car.SetSpeed(19) == false);

		REQUIRE(car.SetSpeed(20) == true);

		REQUIRE(car.SetGear(1) == true);
		REQUIRE(car.SetSpeed(31) == false);
		REQUIRE(car.SetSpeed(0) == true);
	}
}