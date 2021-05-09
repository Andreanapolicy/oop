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

	CRational const operator+=(const CRational& fraction);

	CRational const operator-=(const CRational& fraction);

	CRational const operator*=(const CRational& fraction);

	CRational const operator/=(const CRational& fraction);

	friend CRational const operator+(const CRational& firstFraction, const CRational& secondFraction);

	friend CRational const operator-(const CRational& firstFraction, const CRational& secondFraction);

	friend CRational const operator/(const CRational& firstFraction, const CRational& secondFraction);

	friend CRational const operator*(const CRational& firstFraction, const CRational& secondFraction);

	friend bool const operator==(const CRational& firstFraction, const CRational& secondFraction);

	friend bool const operator!=(const CRational& firstFraction, const CRational& secondFraction);

	friend std::ostream& operator<<(std::ostream& iss, const CRational& fraction);

	friend std::istream& operator>>(std::istream& iss, CRational& fraction);

private:
	void Normalize();

	int m_numerator;
	int m_denominator;
};
