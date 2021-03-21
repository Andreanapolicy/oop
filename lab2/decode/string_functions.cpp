#include "string_functions.h"

void DecodeText(std::istream& inFile, std::ostream& outFile)
{
	auto DecodeList = initHTMLDecodeList();

	int maxLengthOfReplacement = GetMaxLengthOfReplacements(DecodeList.replacementList);

	std::string line;

	while (std::getline(inFile, line))
	{
		outFile << DecodeLine(line, maxLengthOfReplacement, DecodeList) << std::endl;
	}
}

HTMLDecodeList initHTMLDecodeList()
{
	HTMLDecodeList DecodeList;
	DecodeList.replacementList = { "&lt;", "&gt;", "&quot;", "&apos;", "&amp;" };
	DecodeList.substituteList = { '<', '>', '\"', '\'', '&' };

	return DecodeList;
}

std::string DecodeLine(const std::string_view& line, const int maxLengthOfReplacement, const HTMLDecodeList& DecodeList)
{
	size_t cursorPos = 0;
	std::string replacedString;
	while (cursorPos < line.length())
	{
		size_t substringBeginPos = line.find('&', cursorPos);
		replacedString.append(line, cursorPos, substringBeginPos - cursorPos);

		if (substringBeginPos == std::string::npos)
		{
			break;
		}

		replacedString += ReplaceCharNearbyPos(line.substr(substringBeginPos, maxLengthOfReplacement), substringBeginPos, DecodeList);

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

char ReplaceCharNearbyPos(const std::string_view& line, size_t& substringBeginPos, const HTMLDecodeList& DecodeList)
{
	char replacedString = '&';

	for (size_t index = 0; index < DecodeList.replacementList.size(); index++)
	{
		auto findReplacement = line.find(DecodeList.replacementList[index]);
		if (findReplacement != std::string::npos && findReplacement == 0)
		{
			replacedString = DecodeList.substituteList[index];
			substringBeginPos += findReplacement + DecodeList.replacementList[index].size() - 1;
			break;
		}
	}

	substringBeginPos++;

	return replacedString;
}
