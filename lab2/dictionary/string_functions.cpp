#include "string_functions.h"
#include <algorithm>

std::optional<std::vector<std::string>> GetVectorFromString(const std::string& line, const std::string& separator)
{
	std::stringstream iss(line);
	std::vector<std::string> words;
	std::string word;

	while (iss.good())
	{
		std::getline(iss, word, ':');
		words.push_back(word);
	}

	return { words };
}

void WriteVectorWithSeparator(std::ostream& outFile, const std::vector<std::string>& vector, const std::string& separator)
{
	for (auto element: vector)
	{
		outFile << element << separator;
	}
}

std::string GetStringInLowerCase(const std::string& line)
{
	std::string stringInLowerCase;
	for (auto element: line)
	{
		stringInLowerCase += tolower(element);
	}

	return stringInLowerCase;
}