#include <iostream>
#include <map>
#include <optional>

typedef std::map<std::string, char> ReplaceList;

void DecodeText(std::istream& inFile, std::ostream& outFile);
int GetMaxLenghtOfReplacements(const ReplaceList& chars);
std::string DecodeLine(std::string& line, const int maxLenghtOfReplacement, ReplaceList& chars);
bool IsHtmlCode(const std::string& code, const ReplaceList& chars);
