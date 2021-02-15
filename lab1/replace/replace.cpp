#include <fstream>
#include <iostream>
#include <string>

struct Args
{
	std::string inputPath;
	std::string outputPath;
};

std::string replaceSubstring(std::string& const searchString, std::string& const replacementString, std::string& const line)
{
	size_t cursorPos = 0;
	std::string replacedString = "";

	while (cursorPos < line.length())
	{
		size_t substringPos = line.find(searchString);
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

int copyFilesWithReplace(std::ifstream& inputFile, std::ofstream& outputFile, std::string& const searchString, std::string& const replacementString)
{
	std::string line;

	while (std::getline(inputFile, line))
	{
		outputFile << replaceSubstring(searchString, replacementString, line) << std::endl;
	}
}

int copyFile(std::ifstream& inputFile, std::ofstream& outputFile)
{
	char ch;
	while (inputFile.get(ch))
	{
		if (!outputFile.put(ch))
		{
			std::cout << "Failed to save copy";
			return 1;
		}
	}

	if (!outputFile.flush())
	{
		std::cout << "Failed to copy data";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Wrond input. Params should be: copyfile.exe <input file name> <output file name>" << std::endl;
		return 1;
	}

	struct Args args = { argv[1], argv[2] };

	std::ifstream inputFile;
	inputFile.open(args.inputPath);
	if (!inputFile.is_open())
	{
		std::cout << "Input file does not opened" << std::endl;
		return 1;
	}

	std::ofstream outputFile;
	outputFile.open(args.outputPath);
	if (!outputFile.is_open())
	{
		std::cout << "Output file does not opened" << std::endl;
		return 1;
	}

	std::string searchString = argv[3];
	std::string replacementString = argv[4];

	if (!searchString.empty() || searchString != replacementString)
	{
		return copyFile(inputFile, outputFile);
	}

	copyFilesWithReplace(inputFile, outputFile, searchString, replacementString);

	if (!outputFile.flush())
	{
		return 1;
	}

	return 0;
}
