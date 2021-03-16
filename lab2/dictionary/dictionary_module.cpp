#include "dictionary_module.h"

void RunDictionary(std::istream& inFile, std::ostream& outFile, const std::string& dictionaryPath)
{
	std::ifstream dictionaryFile;
	dictionaryFile.open(dictionaryPath);
	Dictionary dictionary;

	if (dictionaryFile.is_open())
	{
		dictionary = ReadDictionary(dictionaryFile);
	}

	bool willSave = false;

	RunChat(inFile, outFile, dictionary, willSave);

	/*if (willSave)
	{
		SaveDictionary(dictionaryPath)
	}*/
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
	for (auto element : dictionary)
	{
		std::cout << element.first << ':';
		WriteVectorWithSeparator(std::cout, element.second, ", ");
		std::cout << std::endl;
	}
}

void RunChat(std::istream& inFile, std::ostream& outFile, Dictionary& dictionary, bool& willSave)
{
	std::string line;
	std::string newWord;
	States state = States::START;
	Translation translation;

	while (inFile >> line)
	{
		if (state == States::END)
		{
			if (willSave)
			{
				state = States::END_SAVE;
			}
			WriteMessage(outFile, state);
			//SaveDictionary if willSave
			break;
		}

		if (line == "...")
		{
			state = States::END;
			WriteMessage(outFile, state);
		}

		if (state == States::START)
		{
			auto it = dictionary.find(line);

			if (dictionary.find(line) == dictionary.end())
			{
				state = States::NEW_WORD;
				newWord = line;
			}

			WriteMessage(outFile, state, it->second);
		}

		if (state == States::NEW_WORD)
		{
			auto it = dictionary.find(line);

			if (!line.empty())
			{
				willSave = true;
				AddNewPosInDictionary(newWord, line, dictionary);
				WriteMessage(outFile, state);
				state = States::START;
			}
			else
			{
				newWord = "";
				state = States::START;
			}
		}
	}
}

std::optional<Translation> findTranslation(const std::string& line, Dictionary& dictionary)
{
	auto translation = dictionary.find(line);

	if (translation == dictionary.end())
	{
		return std::nullopt;
	}

	return { translation->second };
}

void WriteMessage(std::ostream& outFile, States state, const Translation& translation)
{
	switch (state)
	{
	case States::START:
		WriteTranslation(outFile, translation);
		break;
	case States::END_SAVE:
		outFile << "There are some changes in your dictionary. Type <yes>, if you want save it, or smth else, if you dont want it.";
		break;
	case States::END:
		outFile << "Alright. See you later.";
		break;
	case States::NEW_WORD:
		outFile << "There is no translation for that word. Type translation and dictionary will be changed, or just type empty string";
		break;
	case States::NEW_TRANSLATION:
		outFile << "New word with translation were added in dictionary";
		break;
	}
}

void WriteTranslation(std::ostream& outFile, const Translation& translation)
{
	for (auto element : translation)
	{
		outFile << element << ' ';
	}
}