#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <vector>
#include <numeric>

std::optional<std::vector<double>> ReadNumbers(std::istream& inFile);
void OutputVector(std::ostream& outFile, const std::vector<double>& vector);
void ProcessVector(std::vector<double>& vector);

int main(int argc, char* argv[])
{
	try
	{
		auto numbers = ReadNumbers(std::cin);

		if (!numbers.has_value())
		{
			throw std::invalid_argument("Wrong input of numbers.");
		}

		ProcessVector(numbers.value());

		std::sort(numbers.value().begin(), numbers.value().end());
		OutputVector(std::cout, numbers.value());
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}

std::optional<std::vector<double>> ReadNumbers(std::istream& inFile)
{
	std::vector<double> vector;

	double number;

	while (inFile >> number)
	{
		vector.push_back(number);
	}

	if (!inFile.eof() || inFile.bad())
	{
		return std::nullopt;
	}

	return { vector };
}

void OutputVector(std::ostream& outFile, const std::vector<double>& vector)
{
	for (auto const& element: vector)
	{
		outFile << element << " ";
	}

	outFile << std::endl;
}

void ProcessVector(std::vector<double>& vector)
{
	double maxElement = *std::max_element(vector.begin(), vector.end());

	std::transform(vector.begin(), vector.end(), vector.begin(), [maxElement](const double element) { return element * 2 / maxElement; });
}