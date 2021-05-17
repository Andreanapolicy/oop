#include "common_libs.h"
#include "CStringStack.h";

int main()
{
	CStringStack stack("test");

	std::cout << stack.Pop() << std::endl;
	std::string isEmpty = stack.IsEmpty() ? "true" : "false";
	std::cout << isEmpty << std::endl;
	return 0;
}