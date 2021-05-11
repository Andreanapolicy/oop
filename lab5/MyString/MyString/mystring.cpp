#include "CMyString.h"
#include "common_libs.h"

int main()
{
	std::string emptyString = "hello world";
	CMyString string = emptyString;
	const char* substring = string.GetSubString(4, 4).GetStringData();

	std::cout << substring << std::endl;
	std::cout << substring[0] << std::endl;
}