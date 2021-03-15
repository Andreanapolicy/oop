#include "map_functions.h"

void RunDictionary(std::istream& inFile, std::ostream& outFile, const std::string& dictionaryPath)
{
	std::ifstream dictionaryFile;
	dictionaryFile.open(dictionaryPath);
	Dictionary dictionary;

	if (dictionaryFile.is_open())
	{
		dictionary = ReadDictionary(dictionaryFile);
	}
	else
	{
		std::cout << "There is no file, bro" << std::endl;
	}
}

Dictionary ReadDictionary(std::istream& dictionaryFile)
{
	Dictionary dictionary;
	std::string line;
	while (dictionaryFile.good())
	{
		std::getline(dictionaryFile, line);
		std::stringstream iss(line);
		std::string word;
		std::string translations;

		std::getline(iss, word, '-');
		std::getline(iss, translations);

		if (!word.empty() && !translations.empty())
		{
			AddNewPosInDictionary(GetStringInLowerCase(word), GetStringInLowerCase(translations), dictionary);
		}
	}

	WriteDictionary(dictionary, std::cout);

	return dictionary;
}

void AddNewPosInDictionary(const std::string& word, const std::string& translations, Dictionary& dictionary)
{
	std::optional<Translation> translationsVector = GetVectorFromString(translations, ", ");

	if (!translationsVector.has_value())
	{
		throw std::invalid_argument("Wrong dictionary. There are no meanings of word");
	}

	auto it = dictionary.find(word);

	if (it == dictionary.end())
	{
		dictionary.insert(std::pair<std::string, Translation>(word, translationsVector.value()));
	}
	else
	{
		it->second.insert(it->second.end(), translationsVector.value().begin(), translationsVector.value().end());
	}
}

void WriteDictionary(Dictionary& dictionary, std::ostream& dictionaryFile)
{
	for (auto element: dictionary)
	{
		std::cout << element.first << ':';
		WriteVectorWithSeparator(std::cout, element.second, ", ");
		std::cout << std::endl;
	}
}