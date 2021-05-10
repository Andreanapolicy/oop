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

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_string;
}