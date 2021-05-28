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

void CStringStack::Delete(Node* pointer)
{
	if (m_size == 0 || m_first == nullptr)
	{
		return;
	}

	delete pointer;
}

void CStringStack::Push(const std::string& value)
{
	auto newNode = new Node(nullptr, value);
	
	newNode->m_next = m_first->m_next;
	m_first->m_next = newNode;

	m_size++;
}

bool CStringStack::IsEmpty() const
{
	return m_size == 0;
}

int CStringStack::Size() const
{
	return m_size;
}