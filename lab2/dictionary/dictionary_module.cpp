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

	bool willSave = false;

	RunChat(inFile, outFile, dictionary, willSave, dictionaryPath);
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

void RunChat(std::istream& inFile, std::ostream& outFile, Dictionary& dictionary, bool& willSave, const std::string& dictionaryPath)
{
	std::string line;
	std::string newWord;
	States state = States::START;
	Translation translation;

	outFile << "> ";
	while (getline(inFile, line))
	{
		if (state == States::END || state == States::END_SAVE)
		{
			if (GetStringInLowerCase(line) == "yes")
			{
				state = States::END_SAVE_SUCCESS;
				WriteMessage(outFile, state);
			}
			
			SaveDictionary(dictionaryPath, dictionary);
			WriteMessage(outFile, States::END);

			break;
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

		if (state == States::START)
		{
			auto it = dictionary.find(GetStringInLowerCase(line));

			if (it == dictionary.end())
			{
				state = States::NEW_WORD;
				newWord = line;
				WriteMessage(outFile, state);
			}
			else
			{
				WriteMessage(outFile, state, it->second);
			}

			continue;
		}

		if (state == States::NEW_WORD)
		{
			auto it = dictionary.find(line);

			if (!line.empty())
			{
				willSave = true;
				AddNewPosInDictionary(GetStringInLowerCase(newWord), GetStringInLowerCase(line), dictionary);
				AddNewPosInDictionary(GetStringInLowerCase(line), GetStringInLowerCase(newWord), dictionary);
				WriteMessage(outFile, States::NEW_TRANSLATION);
			}

			state = States::START;

			continue;
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
		outFile << "There are some changes in your dictionary. Type <yes>, if you want save it, or smth else, if you dont want it." << std::endl;
		break;
	case States::END:
		outFile << "Alright. See you later." << std::endl;
		break;
	case States::NEW_WORD:
		outFile << "There is no translation for that word. Type translation and dictionary will be changed, or just type empty string" << std::endl;
		break;
	case States::NEW_TRANSLATION:
		outFile << "New word with translation were added in dictionary" << std::endl;
		break;
	}

	outFile << "> ";
}

void WriteTranslation(std::ostream& outFile, const Translation& translation)
{
	for (auto element : translation)
	{
		outFile << element << ', ';
	}

	outFile << std::endl;
}

void SaveDictionary(const std::string& outPath, const Dictionary& dictionary)
{
	std::ofstream outFile;

	outFile.open(outPath);

	if (outFile.is_open())
	{
		throw std::runtime_error("There are writing problems with your file.");
	}

	for (auto element : dictionary)
	{
		outFile << element.first << " : ";
		WriteTranslation(outFile, element.second);
	}
}