#pragma once

#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <set>

#include "string_functions.h"

const std::string DICTIONARY_PATH_DEFAULT = "c:/dev/oop/lab2/dictionary/dictionary.txt";

struct Args
{
	std::string DictionaryPath;
};

typedef std::set<std::string> Translation;

typedef std::multimap<std::string, Translation> Dictionary;

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

void AddPosInDictionary(const std::string& word, const Translation& translations, Dictionary& dictionary);

void WriteDictionary(std::ostream& dictionaryFile, const Dictionary& dictionary);

void RunChat(std::istream& inFile, std::ostream& outFile, Dictionary& dictionary, const std::string& dictionaryPath);

std::optional<Translation> FindTranslation(const std::string& line, Dictionary& dictionary);

void WriteMessage(std::ostream& outFile, States state, const Translation& translation = {});

void WriteTranslation(std::ostream& outFile, const Translation& translation);

void SaveDictionary(std::ostream& outFile, const std::string& dictPath, const Dictionary& dictionary);
