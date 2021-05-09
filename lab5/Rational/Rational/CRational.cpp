#include "CRational.h"
#include "common_libs.h"

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("denominator can't be 0");
	}

	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}

	m_numerator = numerator;
	m_denominator = denominator;

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return m_numerator / m_denominator;
}

void CRational::Normalize()
{
	int GCD = GetGreatestCommonDivisor(m_numerator, m_denominator);

	m_numerator /= GCD;
	m_denominator /= GCD;
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const operator+(const CRational& firstFraction, const CRational& secondFraction)
{
	return CRational(firstFraction.m_numerator * secondFraction.m_denominator + 
		firstFraction.m_denominator * secondFraction.m_numerator, firstFraction.m_denominator * secondFraction.m_denominator);
}

CRational const operator-(const CRational& firstFraction, const CRational& secondFraction)
{
	return firstFraction + (-secondFraction);
}

CRational const CRational::operator+=(const CRational& fraction)
{
	*this = CRational(this->m_numerator, this->m_denominator) + fraction;

	Normalize();

	return *this;
}

CRational const CRational::operator-=(const CRational& fraction)
{
	*this = CRational(this->m_numerator, this->m_denominator) - fraction;

	Normalize();

	return *this;
}

CRational const CRational::operator*=(const CRational& fraction)
{
	*this = CRational(this->m_numerator, this->m_denominator) * fraction;

	Normalize();

	return *this;
}

CRational const CRational::operator/=(const CRational& fraction)
{
	*this = CRational(this->m_numerator, this->m_denominator) / fraction;

	Normalize();

	return *this;
}

CRational const operator*(const CRational& firstFraction, const CRational& secondFraction)
{
	return CRational(firstFraction.m_numerator * secondFraction.m_numerator, firstFraction.m_denominator * secondFraction.m_denominator);
}

CRational const operator/(const CRational& firstFraction, const CRational& secondFraction)
{
	if (secondFraction.m_numerator == 0)
	{
		throw std::invalid_argument("Error while dividing on 0");
	}

	CRational invertedFraction(secondFraction.m_denominator, secondFraction.m_numerator);

	return firstFraction * invertedFraction;
}

bool const operator==(const CRational& firstFraction, const CRational& secondFraction)
{
	return firstFraction.m_numerator == secondFraction.m_numerator && firstFraction.m_denominator == secondFraction.m_denominator;
}

bool const operator!=(const CRational& firstFraction, const CRational& secondFraction)
{
	return !(firstFraction == secondFraction);
}

bool const operator>(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator > 0;
}

bool const operator>=(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator >= 0;
}

bool const operator<(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator < 0;
}

bool const operator<=(const CRational& firstFraction, const CRational& secondFraction)
{
	CRational resultFraction = firstFraction - secondFraction;

	return resultFraction.m_numerator <= 0;
}

std::ostream& operator<<(std::ostream& oss, const CRational& fraction)
{
	oss << fraction.m_numerator << '/' << fraction.m_denominator;

	return oss;
}

std::istream& operator>>(std::istream& iss, CRational& fraction)
{
	char delimiter;

	iss >> fraction.m_numerator >> delimiter >> fraction.m_denominator;
	fraction.Normalize();

	return iss;
}
