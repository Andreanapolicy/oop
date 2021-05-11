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

	for (size_t i = 0; i < m_length; i++)
	{
		m_string[i] = pString[i];
	}

	m_string[m_length] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (length < 0)
	{
		throw std::invalid_argument("Error, length is < 0");
	}

	m_length = length;
	m_string = new char[m_length + 1];

	for (size_t i = 0; i < m_length; i++)
	{
		m_string[i] = pString[i];
	}

	m_string[m_length] = '\0';
}

CMyString::CMyString(const CMyString& string)
{
	m_length = string.m_length;
	m_string = new char[m_length + 1];

	for (size_t i = 0; i < m_length; i++)
	{
		m_string[i] = string.m_string[i];
	}

	m_string[m_length] = '\0';
}

CMyString::CMyString(CMyString&& string)
{
	m_length = string.m_length;
	m_string = new char[m_length + 1];

	for (size_t i = 0; i < m_length; i++)
	{
		m_string[i] = string.m_string[i];
	}

	m_string[m_length] = '\0';

	string.m_length = 0;
	string.m_string = nullptr;
}

CMyString::CMyString(const std::string& stlString)
{
	m_length = std::size(stlString);
	m_string = new char[m_length + 1];

	for (size_t i = 0; i < m_length; i++)
	{
		m_string[i] = stlString[i];
	}

	m_string[m_length] = '\0';
}

CMyString const CMyString::operator=(const CMyString& string)
{
	m_length = string.m_length;
	m_string = string.m_string;

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
