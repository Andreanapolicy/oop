#pragma once

template <typename T>
class CMyList
{
	class Node
	{
	public:
		Node(Node* next = nullptr, Node* prev = nullptr)
		{
			this->m_next = next;
			this->m_prev = prev;
		}

		virtual ~Node() = default;

		Node* m_next;
		Node* m_prev;
	};

	/*class NodeWithValue : public Node
	{
	public:
		NodeWithData(Node* next, Node* prev, const T& value)
			: Node(next, prev)
			, m_value(value)
		{
		}

		T GetValue() const
		{
			return m_value;
		}

		std::string Dwda()
		{
			return "asdas";
		}

	private:
		T m_value;
	}*/

public:
	CMyList()
	{
		m_first = new Node();
		m_last = new Node();
		m_size = 0;
	}

	~CMyList()
	{
		if (!IsEmpty())
		{
			DeleteTop();
		}

		delete m_first;
		delete m_last;
	}

	void DeleteTop()
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

	CMyList(const CMyList& list)
	{
	
	}

	CMyList(CMyList&& list);

	void PushBack(const T& value);

	void PushFront(const T& value);

	bool IsEmpty() const
	{
		return m_size == 0;
	}

	int Size() const
	{
		return m_size;
	}


private:
	

	Node* m_first;
	Node* m_last;

	int m_size;
};
