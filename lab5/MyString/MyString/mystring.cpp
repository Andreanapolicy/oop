#include "CMyString.h"
#include "common_libs.h"

int main()
{
	CMyString string("testetstetst123");
	string.GetLength();
	const char* string2 = string.GetStringData();
	std::cout << string2 << std::endl;
}