#include <iostream>
#include <map>
#include <optional>

typedef std::map<std::string, char> ReplaceList;

void DecodeText(std::istream& inFile, std::ostream& outFile);

std::string DecodeLine(std::string& line, const int maxLenghtOfReplacement, ReplaceList& chars);

int GetMaxLenghtOfReplacements(const ReplaceList& chars);

bool IsHtmlCode(const std::string& code, const ReplaceList& chars);
