#pragma once
#include "common_libs.h"

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;

	int GetDenominator() const;

	double ToDouble() const;

	CRational const operator+() const;

	CRational const operator-() const;

private:
	void Normalize();

	int m_numerator;
	int m_denominator;
};
