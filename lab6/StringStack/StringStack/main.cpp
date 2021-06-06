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

	CStringStack newStack = stack;
}