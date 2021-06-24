#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../SearchServer/SearchServer.h"

TEST_CASE("test functional of constructor")
{
	GIVEN("search server")
	{
		SearchServer searchServer;

		THEN("docs count = 0")
		{
			REQUIRE(searchServer.GetDocsCount() == 0);
		}
	}
}