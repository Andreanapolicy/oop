#include "common_libs.h"
#include "CStringStack.h"

int main()
{
	CStringStack stack;

	stack.Push("1");
	stack.Push("2");
	stack.Push("3");
	stack.Push("4");
	stack.Push("5");

	std::cout << stack.Pop() << std::endl;
	std::cout << std::to_string(stack.Size()) << std::endl;
	std::cout << std::to_string(stack.IsEmpty()) << std::endl;
}