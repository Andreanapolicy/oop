#include "algorithms.h"

int GetGreatestCommonDivisor(int firstNumber, int secondNumber)
{
	firstNumber = abs(firstNumber);
	secondNumber = abs(secondNumber);

	if (firstNumber == 0 && secondNumber == 0)
	{
		throw std::invalid_argument("There is no GCD for numbers (0; 0)");
	}

	if (firstNumber == 0 || secondNumber == 0)
	{
		return (firstNumber + secondNumber);
	}

	if (firstNumber > secondNumber)
	{
		return GetGreatestCommonDivisor(firstNumber % secondNumber, secondNumber);
	}

	return GetGreatestCommonDivisor(firstNumber, secondNumber % firstNumber);
}