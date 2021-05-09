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