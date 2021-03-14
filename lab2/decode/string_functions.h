#include <iostream>
#include <vector>
#include <optional>

typedef std::vector<std::string> ReplacementList;
typedef std::vector<char> SubstituteList;

void DecodeText(std::istream& inFile, std::ostream& outFile);

std::string DecodeLine(const std::string& line, const int maxLengthOfReplacement, const ReplacementList& replacementChars, const SubstituteList& substituteChars);

int GetMaxLengthOfReplacements(const ReplacementList& chars);

bool IsHtmlCode(const std::string& code, const ReplacementList& chars);

std::string ReplaceCharsNearbyPos(const std::string& line, size_t& substringBeginPos, const ReplacementList& replacementChars, const SubstituteList& substituteChars);