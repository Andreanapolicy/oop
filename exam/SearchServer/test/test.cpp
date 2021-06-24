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

TEST_CASE("test functional of adding document")
{
	GIVEN("search server")
	{
		SearchServer searchServer;

		THEN("docs count = 0")
		{
			REQUIRE(searchServer.GetDocsCount() == 0);
		}

		WHEN("add empty doc")
		{
			searchServer.AddDoc("");

			THEN("docs count = 0")
			{
				REQUIRE(searchServer.GetDocsCount() == 0);	
			}
		}

		WHEN("add 1 doc")
		{
			searchServer.AddDoc("first");

			THEN("docs count = 1")
			{
				REQUIRE(searchServer.GetDocsCount() == 1);	
			}
		}

		WHEN("add 2 doc")
		{
			searchServer.AddDoc("first");
			searchServer.AddDoc("second");

			THEN("docs count = 2")
			{
				REQUIRE(searchServer.GetDocsCount() == 2);	
			}
		}
	}
}