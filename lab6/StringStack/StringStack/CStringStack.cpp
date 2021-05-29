#include "CStringStack.h"
#include "CEmptyStackError.h"
#include "COverflowStackError.h"
#include "common_libs.h"

CStringStack::CStringStack()
{
	m_size = 0;
	m_first = new Node();
}

CStringStack::~CStringStack()
{
	if (m_size == 0 || m_first == nullptr)
	{
		return;
	}

	while (!IsEmpty())
	{
		auto futureFirst = m_first->m_next->m_next;
		delete m_first->m_next;
		m_first->m_next = futureFirst;

		m_size--;
	}
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

CStringStack::CStringStack(CStringStack&& stack)
{
	m_size = stack.m_size;
	m_first = new Node();
	m_first->m_next = stack.m_first->m_next;

	stack.m_first->m_next = nullptr;
}

void CStringStack::DeleteTop()
{
	if (m_size == 0 || m_first == nullptr)
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

	auto futureFirst = m_first->m_next->m_next;
	delete m_first->m_next;
	m_first->m_next = futureFirst;

	m_size--;

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