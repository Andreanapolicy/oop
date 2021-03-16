#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary_module.h"

TEST_CASE("Unnecessarily decode text")
{
	REQUIRE(GetStringInLowerCase("HeLLo, How  ARE you?") == "hello, how  are you?");
}