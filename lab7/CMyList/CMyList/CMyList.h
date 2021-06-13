#pragma once
#include "UnableChangeIteratorError.h"
#include "UnableDeleteElementError.h"
#include "UnableInsertElementError.h"
#include "UnableGetElementError.h"

#include <iterator>
#include <stdexcept>
#include <memory>

template <typename T>
class CMyList
{
	class Node
	{
	public:
		Node(Node* prev, std::unique_ptr<Node>&& next)
			: m_prev(prev)
			, m_next(std::move(next))
		{
		}

		virtual T& GetValue()
		{
			throw std::runtime_error("Error, can't get value");
		}

		virtual ~Node() = default;

		Node* m_prev;
		std::unique_ptr<Node> m_next;
	};

	class NodeWithValue : public Node
	{
	public:
		NodeWithValue(Node* prev, std::unique_ptr<Node>&& next, const T& value)
			: Node(prev, std::move(next))
			, m_value(value)
		{
		}

		T& GetValue() override
		{
			return m_value;
		}

		T m_value;
	};

	template<bool IsConst>
	class Iterator
	{
		friend class CMyList;
	public:
		using Type = Iterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
        using pointer = value_type*;

		explicit Iterator(Node* node)
			: m_node(node)
		{
		}

		Iterator(const Iterator& iterator)
			: m_node(iterator.m_node)
		{
		}

		friend bool operator==(const Type& firstIterator, const Type& secondIterator)
		{
			return firstIterator.m_node == secondIterator.m_node;
		}

		friend bool operator!=(const Type& firstIterator, const Type& secondIterator)
		{
			return firstIterator.m_node != secondIterator.m_node;
		}

		Type operator++(int)
		{
			Iterator temp = *this;
			++(*this);

			return temp;
		}

		Type& operator++()
		{
			if (m_node == nullptr || m_node->m_next == nullptr)
			{
				throw UnableChangeIteratorError("Error, unable increase end()");
			}

			m_node = m_node->m_next.get();

			return *this;
		}

		Type operator--(int)
		{
			Iterator temp = *this;
			--(*this);

			return temp;
		}

		Type& operator--()
		{
			if (m_node == nullptr || m_node->m_prev == nullptr)
			{
				throw UnableChangeIteratorError("Error, unable increase begin()");
			}

			m_node = m_node->m_prev;

			return *this;
		}

		reference& operator*() const
		{
			return m_node->GetValue();
		}

	private:
		Node* m_node = nullptr;
	};

public:
	CMyList()
	{
		auto lastNode = std::make_unique<Node>(nullptr, nullptr);
		Node* pLastNode = lastNode.get();

		m_first = std::make_unique<Node>(nullptr, std::move(lastNode));
		m_last = pLastNode;
		m_last->m_prev = m_first.get();
		m_size = 0;
	}

	~CMyList()
	{
		if (!IsEmpty())
		{
			Delete(begin());
		}

		m_first = nullptr;
		m_last = nullptr;
	}

	CMyList(const CMyList& list);

	CMyList(CMyList&& list);

	void PushBack(const T& value)
	{
		Insert(end(), value);
	}

	void PushFront(const T& value)
	{
		Insert(begin(), value);
	}

	bool IsEmpty() const
	{
		return m_size == 0;
	}

	int Size() const
	{
		return m_size;
	}

	using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;

	iterator begin()
	{
		return iterator(m_first->m_next.get());
	}

	iterator end()
	{
		return iterator(m_last);
	}
	
	const_iterator begin() const
	{
		return const_iterator(m_first->m_next.get());
	}

	const_iterator end() const
	{
		return const_iterator(m_last);
	}

	void Insert(const const_iterator& it, const T& value)
	{
		Insert(iterator(it.m_node), value);
	}

	void Insert(const iterator& iterator, const T& value)
	{

		auto newNode = std::make_unique<NodeWithValue>(iterator.m_node->m_prev, std::move(iterator.m_node->m_prev->m_next), value);
		
		newNode->m_next->m_prev = newNode.get();
		newNode->m_prev->m_next = std::move(newNode);
		
		++m_size;
	}

	T& PopFront() const
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_first->m_next->GetValue();
	}

	const T& PopFront()
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_first->m_next->GetValue();
	}

	T& PopBack() const
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_last->m_prev->GetValue();
	}

	const T& PopBack()
	{
		if (IsEmpty())
		{
			throw UnableGetElementError("Error, list is empty");
		}

		return m_last->m_prev->GetValue();
	}

	void Delete(const const_iterator& it)
	{
		Delete(iterator(it.m_node));
	}

	void Delete(const iterator& iterator)
	{
		if (iterator == end() || iterator == --begin())
		{
			throw UnableDeleteElementError("Error, you can't delete element at that position");
		}

		iterator.m_node->m_next->m_prev = iterator.m_node->m_prev;
		iterator.m_node->m_prev->m_next = std::move(iterator.m_node->m_next);

		m_size--;
	}

private:

	std::unique_ptr<Node> m_first;
	Node* m_last;

	int m_size;
};
