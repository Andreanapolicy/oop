#pragma once

#include <codecvt>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

std::optional<std::vector<std::string>> GetVectorFromString(const std::string& line, const std::string& separator);

void WriteVectorWithSeparator(std::ostream& outFile, const std::vector<std::string>& vector, const std::string& separator);

std::string GetStringInLowerCase(const std::string& line);