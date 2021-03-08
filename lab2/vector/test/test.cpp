#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector_functions.cpp"
#include "../vector_functions.h"

TEST_CASE("Reading not sorted numbers vector")
{
	std::istringstream iss("5 54 1 2.3 1 -45.68");
	std::ostringstream oss;
	ReadAndSplitArrayElementsByHalfOfMaximumElement(iss, oss);
	REQUIRE(oss.str() == "-1.692 0.037 0.037 0.085 0.185 2.000 \n");
}

TEST_CASE("Reading sorted numbers vector")
{
	std::istringstream iss("1 2 3 4 5 6 7 8");
	std::ostringstream oss;
	ReadAndSplitArrayElementsByHalfOfMaximumElement(iss, oss);
	REQUIRE(oss.str() == "0.250 0.500 0.750 1.000 1.250 1.500 1.750 2.000 \n");
}

TEST_CASE("Reading wrong numbers vector")
{
	std::istringstream iss("1 2 test 3 4 5 6 7 8");
	std::ostringstream oss;

	REQUIRE_THROWS(ReadAndSplitArrayElementsByHalfOfMaximumElement(iss, oss));
}
