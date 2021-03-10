#include <iostream>
#include <iterator>

#include "string_functions.h"

int main(int argc, char* argv[])
{
	try
	{
		DecodeText(std::cin, std::cout);
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}
