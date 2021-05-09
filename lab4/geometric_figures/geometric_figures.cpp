#include "common_libs.h"
#include "CController.h"

int main()
{
	CController controller(std::cin, std::cout);
	while (!std::cin.eof())
	{
		try
		{
			controller.GetShape();
		}
		catch (const std::exception& error)
		{
			std::cout << error.what() << std::endl;
		}
	}

	controller.WriteAllInfoAboutShapes();
	return 0;
}