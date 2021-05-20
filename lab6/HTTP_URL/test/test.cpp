#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTTP_URL/CHttpUrl.h"
#include "../HTTP_URL/CUrlParsingError.h"

TEST_CASE("Test functional of parsing url with exceptions")
{
	GIVEN("url = 'htt://asd.com/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("htt://asd.com/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("htt://asd.com/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("htt://asd.com/asd/asd"), "Wrong URL");	
		}
	}

	GIVEN("url = '//asd.com/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("//asd.com/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("//asd.com/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("//asd.com/asd/asd"), "Wrong URL");	
		}
	}

	GIVEN("url = 'http://asd.com:0/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("http://asd.com:0/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("http://asd.com:0/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("http://asd.com:0/asd/asd"), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}

	GIVEN("url = 'http://asd.com:65536/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("http://asd.com:65536/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("http://asd.com:65536/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("http://asd.com:65536/asd/asd"), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}

	GIVEN("url = 'http://asd.com:65537/asd/asd'")
	{
		THEN("exception")
		{
			REQUIRE_THROWS(CHttpUrl("http://asd.com:65537/asd/asd"));	
			REQUIRE_THROWS_AS(CHttpUrl("http://asd.com:65537/asd/asd"), CUrlParsingError);	
			REQUIRE_THROWS_WITH(CHttpUrl("http://asd.com:65537/asd/asd"), "Wrong port. Value should be in [1 .. 65535]");	
		}
	}
}

TEST_CASE("Test functional of getter url and others params with rights urls")
{
	GIVEN("url = 'http://regex.com/my_regex'")
	{
		THEN("url = 'http://regex.com/my_regex'")
		{
			CHttpUrl url("http://regex.com/my_regex");
			REQUIRE(url.GetURL() == "http://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("url = 'HTtp://regex.com/my_regex'")
	{
		THEN("url = 'HTtp://regex.com/my_regex'")
		{
			CHttpUrl url("HTtp://regex.com/my_regex");
			REQUIRE(url.GetURL() == "http://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	GIVEN("url = 'https://regex.com/my_regex'")
	{
		THEN("url = 'https://regex.com/my_regex'")
		{
			CHttpUrl url("https://regex.com/my_regex");
			REQUIRE(url.GetURL() == "https://regex.com/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 442);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	GIVEN("url = 'https://regex.com:90/my_regex'")
	{
		THEN("url = 'https://regex.com:90/my_regex'")
		{
			CHttpUrl url("https://regex.com:90/my_regex");
			REQUIRE(url.GetURL() == "https://regex.com:90/my_regex");
			REQUIRE(url.GetDocument() == "/my_regex");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 90);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	GIVEN("url = 'https://regex.com'")
	{
		THEN("url = 'https://regex.com/'")
		{
			CHttpUrl url("https://regex.com");
			REQUIRE(url.GetURL() == "https://regex.com/");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 442);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	GIVEN("url = 'https://regex.com/'")
	{
		THEN("url = 'https://regex.com/'")
		{
			CHttpUrl url("https://regex.com/");
			REQUIRE(url.GetURL() == "https://regex.com/");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetDomain() == "regex.com");
			REQUIRE(url.GetPort() == 442);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}
}