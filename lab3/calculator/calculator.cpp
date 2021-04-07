#include "common_libs.h"
#include "CCalculator.h"
#include "CRemoteController.h"

int main()
{
	CCalculator calculator;
	CRemoteController remoteController(calculator, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}
