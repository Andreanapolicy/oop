#include <fstream>
#include <iostream>
#include <string>

struct Args
{
	std::string inputPath;
	std::string outputPath;
	std::string searchString;
	std::string replacementString;
};

struct Error
{
	std::string message;
};

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

int CopyFile(std::ifstream& inputFile, std::ofstream& outputFile, Error& error)
{
	char ch;
	while (inputFile.get(ch))
	{
		if (!outputFile.put(ch))
		{
			error.message = "Failed to save copy";
			return 1;
		}
	}

	if (!outputFile.flush())
	{
		error.message = "Failed to copy data";
		return 1;
	}

	return 0;
}

int InitArgs(std::ifstream& inputFile, std::ofstream& outputFile, const std::string& searchString, const std::string& replacementString, Error& error)
{
	if (!inputFile.is_open())
	{
		error.message = "Input file does not opened";
		return 1;
	}

	if (!outputFile.is_open())
	{
		error.message = "Output file does not opened";
		return 1;
	}

	if (searchString.empty() || searchString == replacementString)
	{
		return CopyFile(inputFile, outputFile, error);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Wrond input. Params should be: copyfile.exe <input file name> <output file name> <search string> <replacement string>" << std::endl;
		return 1;
	}

	struct Args args = {
		argv[1],
		argv[2],
		argv[3],
		argv[4],
	};

	std::ifstream inputFile;
	inputFile.open(args.inputPath);

	std::ofstream outputFile;
	outputFile.open(args.outputPath);

	Error error;

	if (InitArgs(inputFile, outputFile, args.searchString, args.replacementString, error))
	{
		std::cout << error.message << std::endl;
	}

	CopyFilesWithReplace(inputFile, outputFile, args.searchString, args.replacementString);

	if (!outputFile.flush())
	{
		return 1;
	}

	return 0;
}