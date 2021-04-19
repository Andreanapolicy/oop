#include "common_libs.h"
#include "CController.h"

int main()
{
	CController controller(std::cin, std::cout);
	while (!std::cin.eof())
	{
		controller.GetShape();
	}

	controller.WriteAllInfoAboutShapes();
	return 0;
}