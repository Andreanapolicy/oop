#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <string>

#include "string_functions.h"

namespace
{
ReplaceList htmlSymbols = {
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&quot;", '\"' },
	{ "&apos;", '\'' },
	{ "&amp;", '&' },
};
}

void DecodeText(std::istream& inFile, std::ostream& outFile)
{
	int maxLenghtOfReplacement = GetMaxLenghtOfReplacements(htmlSymbols);

	std::string line;

	while (std::getline(inFile, line))
	{
		outFile << DecodeLine(line, maxLenghtOfReplacement, htmlSymbols) << std::endl;
	}
}

std::string DecodeLine(const std::string& line, const int maxLenghtOfReplacement, ReplaceList& chars)
{
	size_t cursorPos = 0;
	std::string replacedString;
	std::string replacementSubtring;
	while (cursorPos < line.length())
	{
		size_t substringBeginPos = line.find('&', cursorPos);
		replacedString.append(line, cursorPos, substringBeginPos - cursorPos);

		if (substringBeginPos == std::string::npos)
		{
			break;
		}

		size_t substringEndPos = line.find(';', substringBeginPos);

		if (substringEndPos == std::string::npos)
		{
			replacedString.append(line, substringBeginPos, substringEndPos - substringBeginPos);
			break;
		}

		replacementSubtring = line.substr(substringBeginPos, substringEndPos - substringBeginPos + 1);

		if (static_cast<int>(substringEndPos - substringBeginPos) <= maxLenghtOfReplacement && IsHtmlCode(replacementSubtring, chars))
		{
			replacedString += chars[replacementSubtring];
		}
		else
		{
			replacedString.append(replacementSubtring);
		}

		cursorPos = substringEndPos + 1;
	}

	return replacedString;
}

int GetMaxLenghtOfReplacements(const ReplaceList& chars)
{
	int maxLenght = 0;

	if (chars.empty())
	{
		throw std::runtime_error("Replacement dictionary is empty");
	}

	for (auto index = chars.begin(); index != chars.end(); index++)
	{
		maxLenght = static_cast<int>(index->first.length()) > maxLenght ? static_cast<int>(index->first.length()) : maxLenght;
	}

	return maxLenght;
}

bool IsHtmlCode(const std::string& code, const ReplaceList& chars)
{
	return chars.find(code) != chars.end();
}
