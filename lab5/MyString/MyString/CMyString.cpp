#include "CMyString.h"
#include "common_libs.h"

CMyString::CMyString()
{
	m_length = 0;
	m_string = new char[m_length + 1];

	m_string[m_length] = '\0';
}

CMyString::~CMyString()
{
	delete[] m_string;
}

CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	m_string = new char[m_length + 1];

	std::memcpy(m_string, pString, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_string = new char[m_length + 1];

	std::memcpy(m_string, pString, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(const CMyString& string)
{
	m_length = string.m_length;
	m_string = new char[m_length + 1];
	auto tempString = string.GetStringData();

	std::memcpy(m_string, tempString, m_length);
	m_string[m_length] = '\0';
}

CMyString::CMyString(CMyString&& string)
{
	m_string = string.m_string;
	m_length = string.m_length;

	string.m_length = 0;
	string.m_string = nullptr;
}

CMyString::CMyString(const std::string& stlString)
{
	m_length = std::size(stlString);
	m_string = new char[m_length + 1];

	std::memcpy(m_string, &stlString.c_str()[0], m_length);
	m_string[m_length] = '\0';
}

CMyString& CMyString::operator=(const CMyString& string)
{
	if (this == &string)
	{
		return *this;
	}

	char* tempString = new char[string.m_length + 1];

	delete[] m_string;

	std::memcpy(tempString, string.GetStringData(), string.m_length);
	m_length = string.m_length;
	
	m_string = tempString;

	m_string[m_length] = '\0';

	return *this;
}

CMyString& CMyString::operator=(CMyString&& string)
{
	*this = string;

	string.m_string = nullptr;

	return *this;
}

CMyString CMyString::GetSubString(size_t start, size_t length) const
{
	if (m_length < start)
	{
		throw std::invalid_argument("Wrong params");
	}

	length = length + start < m_length ? length : m_length;

	char* tempString = new char[length + 1];

	std::memcpy(tempString, &m_string[start], length);

	tempString[length] = '\0';

	return CMyString(tempString);
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	if (m_string == nullptr)
	{
		return m_empty;
	}

	return m_string;
}

CMyString& CMyString::operator+=(const CMyString& string)
{
	*this = *this + string;

	return *this;
}

CMyString operator+(const CMyString& firstString, const CMyString& secondString)
{
	auto firstStringData = firstString.GetStringData();
	auto secondStringData = secondString.GetStringData();

	CMyString resultString("", firstString.m_length + secondString.m_length);

	std::memcpy(resultString.m_string, firstStringData, firstString.m_length);
	std::memcpy(&resultString.m_string[firstString.m_length], secondStringData, secondString.m_length);

	resultString.m_string[resultString.m_length] = '\0';

	return resultString;
}

bool operator==(const CMyString& firstString, const CMyString& secondString)
{
	if (firstString.m_length != secondString.m_length)
	{
		return false;
	}

	for (size_t i = 0; i < firstString.m_length; i++)
	{
		if (firstString.m_string[i] != secondString.m_string[i])
		{
			return false;
		}
	}

	return true;
}

bool operator<(const CMyString& firstString, const CMyString& secondString)
{
	size_t minLength = std::min(firstString.m_length, secondString.m_length);

	for (size_t i = 0; i < minLength; i++)
	{
		if (firstString[i] > secondString[i])
		{
			return false;
		}

		if (firstString[i] < secondString[i])
		{
			return true;
		}
	}

	if (firstString.m_length >= secondString.m_length)
	{
		return false;
	}

	return true;
}

bool operator>(const CMyString& firstString, const CMyString& secondString)
{
	size_t minLength = std::min(firstString.m_length, secondString.m_length);

	for (size_t i = 0; i < minLength; i++)
	{
		if (firstString[i] < secondString[i])
		{
			return false;
		}

		if (firstString[i] > secondString[i])
		{
			return true;
		}
	}

	if (firstString.m_length <= secondString.m_length)
	{
		return false;
	}

	return true;
}

bool operator<=(const CMyString& firstString, const CMyString& secondString)
{
	return firstString == secondString || firstString < secondString;
}

bool operator>=(const CMyString& firstString, const CMyString& secondString)
{
	return firstString == secondString || firstString > secondString;
}

bool operator!=(const CMyString& firstString, const CMyString& secondString)
{
	return !(firstString == secondString);
}

std::istream& operator>>(std::istream& iss, CMyString& string)
{
	char charForReading = '.';

	std::string resultString;

	if (!iss.good() || iss.eof())
	{
		return iss;
	}

	iss.get(charForReading);
	do
	{
		resultString += charForReading;

	} while (iss.good() && !iss.eof() && iss.get(charForReading));

	string = resultString;

	return iss;
}

const char& CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw std::invalid_argument("Index out of range");
	}

	return m_string[index];
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw std::invalid_argument("Index out of range");
	}

	return m_string[index];
}

std::ostream& operator<<(std::ostream& oss, CMyString& string)
{
	for (size_t i = 0; i < string.GetLength(); i++)
	{
		oss << string.m_string[i];
	}

	return oss;
}
