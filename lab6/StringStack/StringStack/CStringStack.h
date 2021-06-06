#pragma once
#include "CAccessToNonExistentElementError.h"
#include "common_libs.h"

class CStringStack
{
public:

	CStringStack();

	CStringStack(const CStringStack& stack);

	CStringStack(CStringStack&& stack);

	~CStringStack() noexcept;
	
	CStringStack& operator=(const CStringStack& stack);

	CStringStack& operator=(CStringStack&& stack);

	void Push(const std::string& value);

	std::string Pop();

	bool IsEmpty() const;
	
	int Size() const;

private:
	class Node
	{
	public:
		Node(Node* next = nullptr)
		{
			this->m_next = next;
		}

		virtual std::string& GetValue()
		{
			throw CAccessToNonExistentElementError("Error, access to non existent element.");
		}

		virtual ~Node() = default;

		Node* m_next;
	};

	class NodeWithValue : public Node
	{
	public:
		NodeWithValue(Node* next = nullptr, const std::string& value = "")
			: Node(next)
			, m_value(value)
		{
			this->m_next = next;
		}

		std::string& GetValue() override
		{
			return m_value;
		}

	private:
		std::string m_value;
	};

	void DeleteTop() noexcept;

	int m_size;

	Node* m_first;
};
