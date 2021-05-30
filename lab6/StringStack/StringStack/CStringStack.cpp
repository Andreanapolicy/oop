#include "CStringStack.h"
#include "CEmptyStackError.h"
#include "common_libs.h"

CStringStack::CStringStack()
{
	m_size = 0;
	m_first = new Node();
}

CStringStack::~CStringStack()
{
	while (!IsEmpty())
	{
		DeleteTop();
	}

	delete m_first;
}

CStringStack::CStringStack(const CStringStack& stack)
{
	m_size = 0;
	m_first = new Node();

	auto* prevNewStackPtr = m_first;
	auto* nextNewStackPtr = m_first->m_next;
	auto nextOldStackPtr = stack.m_first->m_next;

	while (m_size != stack.m_size)
	{
		nextNewStackPtr = new Node(nullptr, nextOldStackPtr->GetValue());
		prevNewStackPtr->m_next = nextNewStackPtr;
		nextOldStackPtr = nextOldStackPtr->m_next;
		m_size++;
	}
}

CStringStack::CStringStack(CStringStack&& stack) noexcept
{
	m_size = stack.m_size;
	m_first = new Node();
	m_first->m_next = stack.m_first->m_next;

	stack.m_first->m_next = nullptr;
}

void CStringStack::DeleteTop()
{
	if (IsEmpty())
	{
		return;
	}

	auto futureFirst = m_first->m_next->m_next;
	delete m_first->m_next;
	m_first->m_next = futureFirst;

	m_size--;
}

void CStringStack::Push(const std::string& value)
{
	auto newNode = new Node(nullptr, value);
	
	newNode->m_next = m_first->m_next;
	m_first->m_next = newNode;

	m_size++;
}

std::string CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw CEmptyStackError("Error, stack is empty");
	}

	auto popValue = m_first->m_next->GetValue();

	DeleteTop();

	return popValue;
}

bool CStringStack::IsEmpty() const
{
	return m_size == 0;
}

int CStringStack::Size() const
{
	return m_size;
}

CStringStack& CStringStack::operator=(const CStringStack& stack)
{
	if (this == &stack)
	{
		return *this;
	}

	CStringStack tempStack(stack);
	std::swap(*this, tempStack);

	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& stack) noexcept
{
	if (this == &stack)
	{
		return *this;
	}

	while (!IsEmpty())
	{
		DeleteTop();
	}

	m_first = stack.m_first;
	m_size = stack.m_size;

	stack.m_size = 0;
	stack.m_first = new Node();

	return *this;
}