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

	m_length = 0;
}

CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	m_string = new char[m_length + 1];

	CopyString(m_string, pString);
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (length < 0)
	{
		throw std::invalid_argument("Error, length is < 0");
	}

	m_length = length;
	m_string = new char[m_length + 1];

	CopyString(m_string, pString, 0, m_length);
}

CMyString::CMyString(const CMyString& string)
{
	m_length = string.m_length;
	m_string = new char[m_length + 1];

	CopyString(m_string, string.m_string);
}

CMyString::CMyString(CMyString&& string)
{
	m_length = string.m_length;
	m_string = new char[m_length + 1];

	CopyString(m_string, string.m_string);

	string.m_length = 0;
	string.m_string = nullptr;
}

CMyString::CMyString(const std::string& stlString)
{
	m_length = std::size(stlString);
	m_string = new char[m_length + 1];

	CopyString(m_string, &stlString[0]);
}

CMyString CMyString::operator=(const CMyString& string)
{
	if (this == &string)
	{
		return *this;
	}

	delete[] m_string;

	m_length = string.m_length;
	m_string = new char[m_length + 1];

	CopyString(m_string, string.m_string);

	return *this;
}

CMyString CMyString::GetSubString(size_t start, size_t length) const
{
	if (length < start || m_length < start)
	{
		throw std::invalid_argument("Wrong params");
	}

	std::string substring = "";

	length = length < m_length ? length : m_length;

	for (size_t i = start; i < length; i++)
	{
		substring += m_string[i];
	}

	return CMyString(substring);
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_string;
}

CMyString CMyString::operator+=(const CMyString& string)
{
	*this = CMyString(this->m_string, this->m_length) + string;
	
	return *this;
}

CMyString operator+(const CMyString& firstString, const CMyString& secondString)
{
	CMyString resultString = firstString;

	delete[] resultString.m_string;

	resultString.m_length += secondString.m_length;
	resultString.m_string = new char[resultString.m_length + 1];

	resultString.CopyString(resultString.m_string, firstString.m_string);
	resultString.CopyString(resultString.m_string, secondString.m_string, firstString.m_length);

	return resultString;
}

void CMyString::CopyString(char* destination, const char* source, size_t startPos, size_t length)
{
	size_t resultLength = std::min(std::strlen(source), length);

	for (size_t i = 0; i < resultLength; i++)
	{
		destination[i + startPos] = source[i];
	}

	destination[resultLength + startPos] = '\0';
}
