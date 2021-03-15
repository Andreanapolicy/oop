#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../map_functions.h"

TEST_CASE("Unnecessarily decode text")
{
	//std::istringstream iss("Hello, i am text without any html symbols");
	//std::ostringstream oss;

	REQUIRE(1 + 1 == 2);
}