#include "string_functions.h"

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
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
	auto& facet = std::use_facet<std::ctype<wchar_t>>(std::locale());
	std::wstring str = StringToWstring(line);
	facet.tolower(&str[0], &str[0] + str.size());

	return WstringToString(str);
}

std::wstring StringToWstring(const std::string& line)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(line);
}

std::string WstringToString(const std::wstring& line)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(line);
}