#pragma once
#include "common_libs.h"

class CStringStack
{
public:
	CStringStack();

	~CStringStack();

	CStringStack(const std::string& string);

	void Push(const std::string& string);

	std::string Pop();

	bool IsEmpty() const;

	int Size() const;

private:

	void DecreaseStack();

	int m_top;
	std::string* m_stack;
};
