#include "dictionary_module.h"

void RunDictionary(std::istream& inFile, std::ostream& outFile, const std::string& dictionaryPath)
{
	std::ifstream dictionaryFile;
	dictionaryFile.open(dictionaryPath);
	Dictionary dictionary = {};

	if (dictionaryFile.is_open())
	{
		dictionary = ReadDictionary(dictionaryFile);
	}

	dictionaryFile.close();

	RunChat(inFile, outFile, dictionary, dictionaryPath);
}

Dictionary ReadDictionary(std::istream& dictionaryFile)
{
	Dictionary dictionary;
	std::string line;
	while (getline(dictionaryFile, line))
	{
		std::stringstream iss(line);
		std::string word;
		std::string translations;

		getline(iss, word, ':');
		getline(iss, translations);

		if (!word.empty() && !translations.empty())
		{
			AddNewPosInDictionary(word, translations, dictionary);
		}
	}

	return dictionary;
}

void AddNewPosInDictionary(const std::string& word, const std::string& translations, Dictionary& dictionary)
{
	std::optional<Translation> translationsSet = GetSetFromString(GetStringInLowerCase(translations), ", ");

	if (!translationsSet.has_value())
	{
		throw std::invalid_argument("Wrong dictionary. There are no meanings of word");
	}

	AddPosInDictionary(GetStringInLowerCase(word), translationsSet.value(), dictionary);

	for (auto element : translationsSet.value())
	{
		AddPosInDictionary(element, GetSetFromString(GetStringInLowerCase(word), " ").value(), dictionary);
	}
}

void AddPosInDictionary(const std::string& word, const Translation& translations, Dictionary& dictionary)
{
	auto it = dictionary.find(word);

	if (it == dictionary.end())
	{
		dictionary.insert(std::pair<std::string, Translation>(word, translations));
	}
	else
	{
		for (auto element : translations)
		{
			it->second.insert(element);
		}
	}
}

void RunChat(std::istream& inFile, std::ostream& outFile, Dictionary& dictionary, const std::string& dictionaryPath)
{
	bool willSave = false;

	std::string line;
	std::string newWord;
	Translation translation;
	States state = States::START;

	outFile << "> ";
	while (getline(inFile, line))
	{
		switch (state)
		{
		case States::END:
		case States::END_SAVE: {
			if (GetStringInLowerCase(line) == "yes")
			{
				state = States::END_SAVE_SUCCESS;
				WriteMessage(outFile, state);
				SaveDictionary(outFile, dictionaryPath, dictionary);
			}

			WriteMessage(outFile, States::END);

			break;
		}
		case States::START: {
			auto it = FindTranslation(line, dictionary);

			if (!it.has_value())
			{
				state = States::NEW_WORD;
				newWord = line;
				WriteMessage(outFile, state);
			}
			else
			{
				WriteMessage(outFile, state, it.value());
			}

			break;
		}
		case States::NEW_WORD: {
			if (!line.empty())
			{
				willSave = true;
				AddNewPosInDictionary(newWord, line, dictionary);
				WriteMessage(outFile, States::NEW_TRANSLATION);
			}
			else
			{
				outFile << "> ";
			}

			state = States::START;

			break;
		}
		}

		if (line == "...")
		{
			state = willSave ? States::END_SAVE : States::END;
			WriteMessage(outFile, state);

			if (!willSave)
			{
				break;
			}
		}
	}
}

std::optional<Translation> FindTranslation(const std::string& line, Dictionary& dictionary)
{
	auto translation = dictionary.find(GetStringInLowerCase(line));

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
		outFile << "> ";
		break;
	case States::END_SAVE:
		outFile << "There are some changes in your dictionary. Type <yes>, if you want save it, or smth else, if you dont want it." << std::endl;
		outFile << "> ";
		break;
	case States::END:
		outFile << "Alright. See you later." << std::endl;
		break;
	case States::NEW_WORD:
		outFile << "There is no translation for that word. Type translation(with delimiter \", \") and dictionary will be changed, or just type empty string" << std::endl;
		outFile << "> ";
		break;
	case States::NEW_TRANSLATION:
		outFile << "New word with translation were added in dictionary" << std::endl;
		outFile << "> ";
		break;
	}
}

void WriteTranslation(std::ostream& outFile, const Translation& translation)
{
	for (auto element : translation)
	{
		auto it = translation.end();
		it--;
		outFile << element << (element != *it ? ", " : "");
	}

	outFile << std::endl;
}

void SaveDictionary(std::ostream& outFile, const std::string& dictPath, const Dictionary& dictionary)
{
	outFile << "Dictionary will be overwritten in " << dictPath << std::endl;
	std::ofstream dictFile;

	dictFile.open(dictPath);

	if (!dictFile.is_open())
	{
		throw std::runtime_error("There are writing problems with your file.");
	}

	WriteDictionary(dictFile, dictionary);
}

void WriteDictionary(std::ostream& dictionaryFile, const Dictionary& dictionary)
{
	for (auto element : dictionary)
	{
		dictionaryFile << element.first << ':';
		WriteTranslation(dictionaryFile, element.second);
		dictionaryFile << std::endl;
	}
}
