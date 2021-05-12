#include "CMyString.h"
#include "common_libs.h"

int main()
{
	std::string emptyString = "hello";
	CMyString string = emptyString;
	CMyString substring = string.GetSubString(1, 2);
	const char* result = substring.GetStringData();

	std::cout << result << std::endl;
	std::cout << result[1] << std::endl;
}