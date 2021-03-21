#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <string>
#include <vector>
#include <string_view>

typedef std::vector<std::string> ReplacementList;
typedef std::vector<char> SubstituteList;

struct HTMLDecodeList
{
	ReplacementList replacementList;
	SubstituteList substituteList;
};

void DecodeText(std::istream& inFile, std::ostream& outFile);

std::string DecodeLine(const std::string_view& line, const int maxLengthOfReplacement, const HTMLDecodeList& DecodeList);

int GetMaxLengthOfReplacements(const ReplacementList& chars);

char ReplaceCharNearbyPos(const std::string_view& line, size_t& substringBeginPos, const HTMLDecodeList& DecodeList);

HTMLDecodeList initHTMLDecodeList();