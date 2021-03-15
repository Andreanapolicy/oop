#pragma once

#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "string_functions.h"

typedef std::vector<std::string> Translation;

typedef std::map<std::string, Translation> Dictionary;

void RunDictionary(std::istream& inFile, std::ostream& outFile, const std::string& dictionaryPath);

Dictionary ReadDictionary(std::istream& dictionaryFile);

void AddNewPosInDictionary(const std::string& word, const std::string& translations, Dictionary& dictionary);

void WriteDictionary(Dictionary& dictionary, std::ostream& dictionaryFile);