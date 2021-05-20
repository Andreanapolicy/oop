#include "CStringStack.h"
#include "CEmptyStackError.h"
#include "COverflowStackError.h"
#include "common_libs.h"

CStringStack::CStringStack()
	: m_stack(new std::string[0])
	, m_top(-1)
{
}

CStringStack::~CStringStack()
{
	delete[] m_stack;
}

CStringStack::CStringStack(const std::string& string)
	: m_top(0)
{
	m_stack = new std::string[1];
	m_stack[0] = string;
}

std::string CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw CEmptyStackError("Stack empty");
	}

	std::string element = m_stack[m_top];

	DecreaseStack();

	return element;
}

void CStringStack::Push(const std::string& string)
{
	if (m_top >= INT_MAX - 1)
	{
		throw COverflowStackError("Stack overflow");
	}

	std::string* tempStack = new std::string[m_top + 2];

	std::memcpy(tempStack, m_stack, m_top + 1);
	tempStack[m_top + 1] = string;

	delete[] m_stack;

	m_stack = tempStack;

	m_top += 1;
}

int CStringStack::Size() const
{
	return m_top + 1;
}

void CStringStack::DecreaseStack()
{
	if (m_top == 0)
	{
		delete[] m_stack;
		
		m_top = -1;

		m_stack = new std::string[0];
		
		return;
	}

	std::string* tempStack = new std::string[m_top];

	std::memcpy(tempStack, m_stack, m_top);

	delete[] m_stack;

	m_stack = tempStack;

	m_top -= 1;
}

bool CStringStack::IsEmpty() const
{
	return m_top < 0;
}