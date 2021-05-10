#pragma once
#include "common_libs.h"

class CMyString
{
public:
	CMyString();

	CMyString(const char* pString);

	size_t GetLength() const;

	const char* GetStringData() const;

	~CMyString();

private:
	char* m_string;
	size_t m_length;
};
