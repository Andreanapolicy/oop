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

enum class States
{
	START = 0,
	NEW_WORD = 1,
	NEW_TRANSLATION = 2,
	END = 3,
	END_SAVE = 4,
	END_SAVE_SUCCESS = 5,
};

void RunDictionary(std::istream& inFile, std::ostream& outFile, const std::string& dictionaryPath);

Dictionary ReadDictionary(std::istream& dictionaryFile);

void AddNewPosInDictionary(const std::string& word, const std::string& translations, Dictionary& dictionary);

void WriteDictionary(Dictionary& dictionary, std::ostream& dictionaryFile);

void RunChat(std::istream& inFile, std::ostream& outFile, Dictionary& dictionary, bool& willSave, const std::string& dictionaryPath);

std::optional<Translation> findTranslation(const std::string& line, Dictionary& dictionary);

void WriteMessage(std::ostream& outFile, States state, const Translation& translation = {});

void WriteTranslation(std::ostream& outFile, const Translation& translation);

void SaveDictionary(const std::string& outPath, const Dictionary& dictionary);
