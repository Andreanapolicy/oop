#pragma once
#include "common_libs.h"

class CStringStack
{
public:

	CStringStack();

	CStringStack(const CStringStack& stack);

	CStringStack(CStringStack&& stack) noexcept;

	~CStringStack();
	
	CStringStack& operator=(const CStringStack& stack);

	CStringStack& operator=(CStringStack&& stack) noexcept;

	void Push(const std::string& value);

	std::string Pop();

	bool IsEmpty() const;
	
	int Size() const;

private:
	class Node
	{
	public:
		Node(Node* next = nullptr, const std::string& value = "")
			: m_value(value)
		{
			this->m_next = next;
		}

		std::string& GetValue()
		{
			return m_value;
		}

		~Node() = default;

		Node* m_next;

	private:
		std::string m_value;
	};

	void DeleteTop();

	int m_size;

	Node* m_first;
};
