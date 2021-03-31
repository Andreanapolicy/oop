#include "common_libs.h"
#include "CCar.h"
#include "RemoteControl.h"

int main()
{
	CCar car;
	RemoteControl remoteController(car, std::cin, std::cout);
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
