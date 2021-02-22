#include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>

struct Args
{
	std::string inputPath;
	std::string outputPath;
	std::string searchString;
	std::string replacementString;
};

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 5)
	{
		return std::nullopt;
	}

	return { { argv[1], argv[2], argv[3], argv[4] } };
}

std::string ReplaceSubstring(const std::string& searchString, const std::string& replacementString, const std::string& line)
{
	size_t cursorPos = 0;
	std::string replacedString;

	while (cursorPos < line.length())
	{
		size_t substringPos = line.find(searchString, cursorPos);
		replacedString.append(line, cursorPos, substringPos - cursorPos);

		if (substringPos == std::string::npos)
		{
			break;
		}

		replacedString.append(replacementString);
		cursorPos = substringPos + searchString.length();
	}

	return replacedString;
}

void CopyFilesWithReplace(std::ifstream& inputFile, std::ofstream& outputFile, const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(inputFile, line))
	{
		outputFile << ReplaceSubstring(searchString, replacementString, line) << std::endl;
	}
}

void CopyFile(std::ifstream& inputFile, std::ofstream& outputFile)
{
	char ch;
	while (inputFile.get(ch))
	{
		if (!outputFile.put(ch))
		{
			throw std::exception("Failed to save copy");
		}
	}

	if (!outputFile.flush())
	{
		throw std::exception("Failed to copy data");
	}
}

void InitFiles(std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		throw std::exception("Input file does not opened");
	}

	if (!outputFile.is_open())
	{
		throw std::exception("Output file does not opened");
	}
}

void Replace(const std::string& inputPath, const std::string& outputPath, const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile;
	inputFile.open(inputPath);

	std::ofstream outputFile;
	outputFile.open(outputPath);

	try
	{
		InitFiles(inputFile, outputFile);
	}
	catch (std::exception& error)
	{
		throw std::exception(error.what());
	}

	if (searchString.empty() || searchString == replacementString)
	{
		try
		{
			CopyFile(inputFile, outputFile);
		}
		catch (std::exception& error)
		{
			throw std::exception(error.what());
		}
	}

	CopyFilesWithReplace(inputFile, outputFile, searchString, replacementString);

	if (!outputFile.flush())
	{
		throw std::exception("Output file is flush");
	}
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);

	if (!args.has_value())
	{
		std::cout << "Wrond input. Params should be: copyfile.exe <input file name> <output file name> <search string> <replacement string>" << std::endl;
		return 1;
	}

	try
	{
		Replace(args->inputPath, args->outputPath, args->searchString, args->replacementString);
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}