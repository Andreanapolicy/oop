#include <iostream>

#include "vector_functions.h"

int main(int argc, char* argv[])
{
	try
	{
		ReadAndSplitArrayElementsByHalfOfMaximumElement(std::cin, std::cout);
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}
