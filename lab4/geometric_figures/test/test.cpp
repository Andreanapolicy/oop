#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../common_libs.h"
#include "../CPoint.h"
#include "../CLineSegment.h"

TEST_CASE("Test class CPoint")
{
	WHEN("Point x = 0; y = 0")
	{
		CPoint point(0, 0);

		THEN("x = 0; y = 0")
		{
			REQUIRE(point.x == 0);
			REQUIRE(point.y == 0);
		}
	}

	WHEN("Point x = -10; y = 10")
	{
		CPoint point(-10, 10);

		THEN("x = -10; y = 10")
		{
			REQUIRE(point.x == -10);
			REQUIRE(point.y == 10);
		}
	}

	WHEN("Point x = 124.123; y = -110.123")
	{
		CPoint point(124.123, -110.123);

		THEN("x = 124.123; y = 10")
		{
			REQUIRE(point.x == 124.123);
			REQUIRE(point.y == -110.123);
		}
	}

	WHEN("Points (1, 2) (2, 1)")
	{
		CPoint firstPoint(1, 2);
		CPoint secondPoint(2, 1);

		THEN("Points are not equal")
		{
			REQUIRE(!CPoint::Equal(firstPoint, secondPoint));
		}
	}

	WHEN("Points (0, 1) (0, -1)")
	{
		CPoint firstPoint(0, 1);
		CPoint secondPoint(0, -1);

		THEN("Points are not equal")
		{
			REQUIRE(!CPoint::Equal(firstPoint, secondPoint));
		}
	}

	WHEN("Points (0, 0) (0, 0)")
	{
		CPoint firstPoint(0, 0);
		CPoint secondPoint(0, 0);

		THEN("Points are equal")
		{
			REQUIRE(CPoint::Equal(firstPoint, secondPoint));
		}
	}
}

TEST_CASE("Test class CLineSegment")
{
	WHEN("Line (1, 1)(2, 2)")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(2, 2);
		CLineSegment line(firstPoint, secondPoint, 0xfff000);

		THEN("area = 0; perimeter = sqrt(2); color = yellow")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == sqrt(2));
			REQUIRE(line.GetOutlineColor() == 0xfff000);
			REQUIRE(CPoint::Equal(line.GetStartPoint(), firstPoint));
			REQUIRE(CPoint::Equal(line.GetEndPoint(), secondPoint));
		}
	}

	WHEN("Line (1, 1)(1, -10)")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(1, -10);
		CLineSegment line(firstPoint, secondPoint, 0xffffff);

		THEN("area = 0; perimeter = 11; color = white")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == 11);
			REQUIRE(line.GetOutlineColor() == 0xffffff);
			REQUIRE(CPoint::Equal(line.GetStartPoint(), firstPoint));
			REQUIRE(CPoint::Equal(line.GetEndPoint(), secondPoint));
		}
	}

	WHEN("Line (1, 1)(1, 1)")
	{
		CPoint firstPoint(1, 1);
		CPoint secondPoint(1, 1);
		CLineSegment line(firstPoint, secondPoint, 0xffffff);

		THEN("area = 0; perimeter = 0; color = white")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == 0);
			REQUIRE(line.GetOutlineColor() == 0xffffff);
			REQUIRE(CPoint::Equal(line.GetStartPoint(), firstPoint));
			REQUIRE(CPoint::Equal(line.GetEndPoint(), secondPoint));
		}
	}
}
