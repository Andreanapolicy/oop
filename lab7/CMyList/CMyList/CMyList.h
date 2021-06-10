#pragma once
#include "UnableChangeIteratorError.h"
#include "UnableDeleteElementError.h"
#include "UnableInsertElementError.h"

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

	class Iterator
	{
		friend class CMyList;
	public:
		Iterator(Node* node)
			: m_node(node)
		{
		}

		Iterator(const Iterator& iterator)
			: m_node(iterator->m_node)
		{
		}

		friend bool operator==(const Iterator& firstIterator, const Iterator& secondIterator)
		{
			return firstIterator.m_node == secondIterator.m_node;
		}

		friend bool operator!=(const Iterator& firstIterator, const Iterator& secondIterator)
		{
			return firstIterator.m_node != secondIterator.m_node;
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			++(*this);

			return temp;
		}

		Iterator& operator++()
		{
			if (m_node == nullptr || m_node->m_next == nullptr)
			{
				throw UnableChangeIteratorError("Error, unable increase end()");
			}

			m_node++;

			return *this;
		}

		Iterator operator--(int)
		{
			Iterator temp = *this;
			--(*this);

			return temp;
		}

		Iterator& operator--()
		{
			if (m_node == nullptr || m_node->m_prev == nullptr)
			{
				throw UnableChangeIteratorError("Error, unable increase begin()");
			}

			m_node--;

			return *this;
		}

		T& operator*() const
		{
			return m_node->getValue();
		}

		Node* operator->() const
		{
			return m_node;
		}

	private:
		Node* m_node = nullptr;
	};

public:
	CMyList()
	{
		std::unique_ptr<Node> last = std::make_unique<Node>(nullptr, nullptr);
		Node* lastPtr = last->get();

		m_first = std::make_unique<Node>(nullptr, std::move(last));
		m_last = lastPtr;

		m_last->m_prev = m_first->get();

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

	void Delete(const Iterator& iterator)
	{
		if (!iterator || iterator == end() || iterator == --begin())
		{
			throw UnableDeleteElementError("Error, you can't delete element at that position");
		}

		iterator->m_next->m_prev = iterator->m_prev;
		iterator->m_prev->m_next = std::move(iterator->m_next);

		m_size--;
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

	Iterator begin() const
	{
		return Iterator(m_first->next->get());
	}

	Iterator end() const
	{
		return Iterator(m_last);
	}

	void Insert(const Iterator& iterator, const T& value)
	{
		if (!iterator.m_node)
		{
			throw UnableInsertElementError("Error, can't insert in this position");
		}

		auto newElement = std::make_unique<NodeWithValue>(iterator->m_prev, std::move(iterator->m_prev->m_next), value);

		newElement->m_next->m_prev = newElement->get();
		newElement->m_prev->m_next = std::move(newElement);

		m_size++;
	}

	int Size() const
	{
		return m_size;
	}

private:

	std::unique_ptr<Node> m_first;
	Node* m_last;

	int m_size;
};
