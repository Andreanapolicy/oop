#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

#define MAX_RADIX 36
#define MIN_RADIX 2

int StringToInt(const std::string& value, int radix);
int CharToInt(const char ch, const int radix);
bool isDigit(const char ch);
bool isLetter(const char ch);
std::string ConvertNumber(const int sourceNotationString, const int destinationNotationString, const std::string& value);
std::string IntToString(int number, const int radix);
char IntToChar(int number, const int radix);


struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		return std::nullopt;
	}

	int sourceNotation;

	try
	{
		sourceNotation = StringToInt(argv[1], 10);
		if (sourceNotation > MAX_RADIX || sourceNotation < MIN_RADIX)
		{
			throw std::exception("Radix is out of range");
		}
	}
	catch (std::exception& error)
	{
		throw std::exception(error.what());
	}

	int destinationNotation;

	try
	{
		destinationNotation = StringToInt(argv[2], 10);
		if (destinationNotation > MAX_RADIX || destinationNotation < MIN_RADIX)
		{
			throw std::exception("Radix is out of range");
		}
	}
	catch (std::exception& error)
	{
		throw std::exception(error.what());
	}

	return { { sourceNotation, destinationNotation, argv[3] } };
}

int StringToInt(const std::string& value, int radix)
{
	if (value.length() < 0)
	{
		throw std::exception("Value is not valid");
	}

	bool isNegative = false;

	if (value[0] == '-')
	{
		isNegative = true;
	}

	int convertedString = 0;

	for (int i = isNegative ? 1 : 0; i < static_cast<int>(value.length()); i++)
	{
		int digit = 0;

		try
		{
			digit = CharToInt(value[i], radix);
			if (convertedString > ((INT_MAX - digit) / radix))
			{
				throw std::exception("Number is out of range");
			}
		}
		catch (std::exception& error)
		{
			throw std::exception(error.what());
		}

		convertedString = convertedString * radix + digit;
	}

	return isNegative ? -convertedString : convertedString;
}

int CharToInt(const char ch, const int radix)
{
	if (isDigit(ch))
	{
		if (ch - '0' >= radix)
		{
			throw std::exception("Wrong number");
		}

		return ch - '0';
	}

	if (isLetter(ch))
	{
		if (ch - 'A' + 10 >= radix)
		{
			throw std::exception("Wrong number");
		}

		return ch - 'A' + 10;
	}

	throw std::exception("Wrong number");
}

bool isDigit(const char ch)
{
	return ch >= '0' && ch <= '9';
}

bool isLetter(const char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

std::string ConvertNumber(const int sourceNotation, const int destinationNotation, const std::string& value)
{
	std::string convertedNumber;

	try
	{
		convertedNumber = IntToString(StringToInt(value, sourceNotation), destinationNotation);
	}
	catch (std::exception& error)
	{
		throw std::exception(error.what());
	}

	return convertedNumber;
}

std::string IntToString(int number, const int radix)
{
	if (number == 0)
	{
		return "0";
	}

	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
		number = -number;
	}

	std::string convertedInt = "";

	while (number > 0)
	{
		try
		{
			convertedInt = convertedInt + IntToChar(number % radix, radix);
		}
		catch (std::exception& error)
		{
			throw std::exception(error.what());
		}

		number = number / radix;
	}

	if (isNegative)
	{
		convertedInt = convertedInt + '-';
	}

	std::reverse(convertedInt.begin(), convertedInt.end());

	return convertedInt;
}

char IntToChar(int number, const int radix)
{
	if (number >= radix)
	{
		throw std::exception("Wrong number");
	}

	if ((number >= 0) && (number <= 9))
	{
		return static_cast<char>('0' + number);
	}

	if ((number >= 10) && (number <= 36))
	{
		return static_cast<char>('A' + (number - 10));
	}

	throw std::exception("Wrong number");
}

int main(int argc, char* argv[])
{
	std::optional<Args> args;
	std::string convertedNumber;

	try
	{
		args = ParseArgs(argc, argv);
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	if (!args.has_value())
	{
		std::cout << "Wrond input. Params should be: radix.exe <source notation> <destination notation> <value>" << std::endl;
		return 1;
	}
	
	try
	{
		convertedNumber = ConvertNumber(args->sourceNotation, args->destinationNotation, args->value);
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	std::cout << convertedNumber << std::endl;

	return 0;
}