#pragma once
#include "common_libs.h"

class CMyString
{
public:
	CMyString();

	CMyString(const char* pString);

	CMyString(const char* pString, size_t length);

	CMyString(const CMyString& string);

	CMyString(CMyString&& string);

	CMyString(std::string const& stlString);

	size_t GetLength() const;

	const char* GetStringData() const;

	CMyString GetSubString(size_t start, size_t length = SIZE_MAX) const;

	CMyString operator=(const CMyString& string);

	~CMyString();

private:
	void CopyString(char* destination, const char* source, size_t startLength = SIZE_MAX);
	char* m_string;
	size_t m_length;
};
