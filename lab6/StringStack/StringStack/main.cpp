#include "common_libs.h"
#include "CStringStack.h"

int main()
{
	CStringStack stack("test1");
	stack.Push("test2");
	stack.Push("test3");
	stack.Push("test4");

	std::cout << stack.Pop() << std::endl;
	std::string isEmpty = stack.IsEmpty() ? "true" : "false";
	std::cout << isEmpty << std::endl;
	return 0;
}