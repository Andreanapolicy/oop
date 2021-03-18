#include "string_functions.h"

namespace
{
SubstituteList substituteList = { '<', '>', '\"', '\'', '&' };
ReplacementList replacementList = { "&lt;", "&gt;", "&quot;", "&apos;", "&amp;" };
}

void DecodeText(std::istream& inFile, std::ostream& outFile)
{
	int maxLengthOfReplacement = GetMaxLengthOfReplacements(replacementList);

	std::string line;

	while (std::getline(inFile, line))
	{
		outFile << DecodeLine(line, maxLengthOfReplacement, replacementList, substituteList) << std::endl;
	}
}

std::string DecodeLine(const std::string& line, const int maxLengthOfReplacement, const ReplacementList& replacementChars, const SubstituteList& substituteChars)
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

		replacementSubtring = ReplaceCharsNearbyPos(line.substr(substringBeginPos, maxLengthOfReplacement), substringBeginPos, replacementChars, substituteChars);

		replacedString.append(replacementSubtring);

		cursorPos = substringBeginPos;
	}

	return replacedString;
}

int GetMaxLengthOfReplacements(const ReplacementList& chars)
{
	if (chars.empty())
	{
		throw std::runtime_error("Replacement dictionary is empty");
	}

	auto maxLength = *std::max_element(chars.begin(), chars.end());

	return maxLength.size();
}

bool IsHtmlCode(const std::string& code, const ReplacementList& chars)
{
	return std::find(chars.begin(), chars.end(), code) != chars.end();
}

std::string ReplaceCharsNearbyPos(const std::string& line, size_t& substringBeginPos, const ReplacementList& replacementChars, const SubstituteList& substituteChars)
{
	std::string replacedString;

	for (size_t index = 0; index < replacementChars.size(); index++)
	{
		auto findReplacement = line.find(replacementChars[index]);
		if (findReplacement != std::string::npos)
		{
			replacedString.append(line, 0, findReplacement);
			replacedString += substituteChars[index];
			substringBeginPos += findReplacement + replacementChars[index].size();
			break;
		}
	}

	if (replacedString.empty())
	{
		replacedString = "&";
		substringBeginPos++;
	}

	return replacedString;
}
