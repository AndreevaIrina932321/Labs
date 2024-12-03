#pragma once

#include <iostream>
#include <vector>
#include <algorithm>


//Обдумать реализацию перехода к следущему элементу, обдумать возвращаемый индекс для вставок и удаления
// написать присваивание или конструктор из итератора/ проверить реализацию по стандартам;


template <typename T>
class List
{
	struct Node;

public:
    template <typename ItemType>
    class TemplateIterator;
    using iterator = TemplateIterator<T>;
    using const_iterator = TemplateIterator<const T>;

public:
	List();
	List(const std::vector<T> &arr);
	List(const List<T> &other);
	~List();

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	int size() const;
	void clear();
	void append(const T& value);
	void print() const;
	void input();
	void swap(List<T> &other) noexcept;
	bool isEmpty() const;

	iterator searchElement(const T &value);
	iterator headInsert(const T &value);
	iterator insertBefore(const T &value);
	iterator insert(int position, const T &value);
	iterator insert(iterator position, const T &value);

	iterator headErase();
	iterator tailErase();
	iterator eraseValue(const T &value);
	iterator erase(int position);
	iterator erase(iterator position);

	void eraseSequence(iterator left, iterator right);
	T max() const;
	T min() const;
	void sort();

	/*
- удаление диапазона элементов с помощью итераторов;
- поиск максимального/минимального элемента;
- сортировка списка;

Необходимые перегрузки:
- присваивание (=);
- получение ссылки на ключ элемента ([ ]);
- сравнение (==, !=);
- сложение (конкатенация) списков (+, +=).
	*/

private:
	int m_size = 0;
	Node* m_head = nullptr;
	Node* m_tail = nullptr;
};

template <typename T>
struct List<T>::Node
{
	Node(Node* next = nullptr, Node* prev = nullptr);
	Node(const T& value, Node* next = nullptr, Node* prev = nullptr);

	T value;
	Node* next = nullptr;
	Node* prev = nullptr;
};


template <typename T>
template <typename ItemType>
class List<T>::TemplateIterator
{
public:
    using value_type = ItemType;
    using reference = ItemType&;
    using pointer = ItemType*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;

    TemplateIterator(Node* node);

    Node *getNode();

    ItemType& operator*();
    const ItemType& operator*() const;
    TemplateIterator operator++();
    TemplateIterator operator--();
    TemplateIterator operator++(int);
    TemplateIterator operator--(int);
    bool operator==(const TemplateIterator& other) const;
    bool operator!=(const TemplateIterator& other) const;

    // написать присваивание или конструктор из итератора/ проверить реализацию по стандартам;

protected:
    Node* m_node = nullptr;
};



template <typename T>
List<T>::List()
	: m_head(new Node())
	, m_tail(new Node())
{
	m_head->next = m_tail;
	m_tail->prev = m_head;
}

template <typename T>
List<T>::List(const std::vector<T> &arr)
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
	m_tail->prev = m_head;
    for (int i = 0; i < arr.size(); ++i)
    {
        append(arr[i]);
    }
}

template <typename T>
List<T>::List(const List<T> &other)
    : m_size(other.m_size)
    , m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
	m_tail->prev = m_head;
    for (const T& value : other)
    {
        append(value);
    }
}

template <typename T>
List<T>::~List()
{
    clear();
    delete m_head;
    delete m_tail;
}

template <typename T> typename
List<T>::iterator List<T>::begin()
{
    return iterator(m_head->next);
}

template <typename T> typename
List<T>::iterator List<T>::end()
{
    return iterator(m_tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(m_head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(m_tail);
}

template <typename T>
int List<T>::size() const
{
    return m_size;
}

template <typename T>
void List<T>::clear()
{
    if (!size())
    {
        return;
    }

    Node* runner = m_head->next;
    while (runner != m_tail)
    {
        Node* node = runner;
        runner = runner->next;
        delete node;
    }
    m_head->next = m_tail;
	m_tail->prev = m_head;
	m_size = 0;
}

template <typename T>
void List<T>::append(const T& value)
{
    Node* node = new Node(value, m_tail, m_tail->prev);
    m_tail->prev->next = node;
    m_tail->prev = node;
    ++m_size;
}

template <typename T>
void List<T>::print() const
{
    for (const T& value : *this)
    {
        std::cout << value << ' ';
    }
    std::cout << "\n";
}

template <typename T>
void List<T>::input()
{
    for (T& value : *this)
    {
        std::cin >> value;
    }
}

template <typename T>
void List<T>::swap(List<T> &other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_tail, other.m_tail);
    std::swap(m_head, other.m_head);
}


template <typename T>
bool List<T>::isEmpty() const
{
    return !m_size;
}

template <typename T>
typename List<T>::iterator List<T>::searchElement(const T &value)
{
    auto it = std::find(begin(), end(), value);
    if (it == end())
    {
        return iterator(nullptr);
    }
    else
    {
        return it;
    }
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator position, const T &value)
{
    /*iterator it = begin();
    while (it != position && it != end())
    {
        ++it;
    }*/
    if (position == end())
    {
        append(value);
        return position;
    }
    Node* node = new Node(value, position.getNode(), position.getNode()->prev);
    position.getNode()->prev->next = node;
    position.getNode()->prev = node;
    ++m_size;
    return --position;
}

template <typename T>
typename List<T>::iterator List<T>::headInsert(const T &value)
{
    return insert(begin(), value);
}

template <typename T>
typename List<T>::iterator List<T>::insertBefore(const T &value)
{
    iterator it = searchElement(value);
    if (it.getNode() == nullptr)
    {
        append(value);
        return it;
    }
    return insert(it, value);
}

template <typename T>
typename List<T>::iterator List<T>::insert(int position, const T &value)
{
    if (position >= m_size)
    {
        append(value);
        return --end();
    }
    iterator it = begin();
    for (int i = 0; i < position; ++i)
    {
        ++it;
    }
    return insert(it, value);
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator position)
{
    /*iterator it = begin();
    while (it != position && it != end())
    {
        ++it;
    }*/
    if (position == end())
    {
        return position;
    }
    position.getNode()->prev->next = position.getNode()->next;
    position.getNode()->next = position.getNode()->prev;
    --m_size;
    delete position.getNode();
    return position;
}

template <typename T>
typename List<T>::iterator List<T>::headErase()
{
    return erase(begin());
}

template <typename T>
typename List<T>::iterator List<T>::tailErase()
{
    return erase(--end());
}

template <typename T>
typename List<T>::iterator List<T>::erase(int position)
{
    if (position >= m_size)
    {
        return end();
    }
    iterator it = begin();
    for (int i = 0; i < position; ++i)
    {
        ++it;
    }
    return erase(it);
}

template <typename T>
typename List<T>::iterator List<T>::eraseValue(const T &value)
{
    iterator it = searchElement(value);
    if (it.getNode() == nullptr)
    {
        return end();
    }
    return erase(it);
}

template <typename T>
void List<T>::eraseSequence(iterator left, iterator right)
{
    iterator it = left;
    while (it != right && it != end())
    {
        ++it;
    }
    /*if (it == end()) //Обдумать реализацию перехода к следущему элементу, обдумать возвращаемый индекс для вставок и удаления
    {
        it = right;
        while (it != left)
        {
            erase(it);
            ++it;
        }
    }
    else
    {
        it = left;
        while (it != right)
        {
            it = erase(it);
        }
    }*/
}

/*template <typename T>
T List<T>::max() const
{

}*/

template <typename T>
List<T>::Node::Node(Node* next, Node* prev)
	: next(next)
	, prev(prev)
{}

template <typename T>
List<T>::Node::Node(const T& value, Node* next, Node* prev)
	: value(value)
	, next(next)
	, prev(prev)
{}

template <typename T>
template <typename ItemType>
List<T>::TemplateIterator<ItemType>::TemplateIterator(Node* node)
    : m_node(node)
{}

template <typename T>
template <typename ItemType>
ItemType& List<T>::TemplateIterator<ItemType>::operator*()
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
const ItemType& List<T>::TemplateIterator<ItemType>::operator*() const
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
List<T>::Node *List<T>::TemplateIterator<ItemType>::getNode()
{
    return m_node;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++()
{
    m_node = m_node->next;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--()
{
    m_node = m_node->prev;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++(int)
{
    TemplateIterator old = *this;
    m_node = m_node->next;
    return old;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--(int)
{
    TemplateIterator old = *this;
    m_node = m_node->prev;
    return old;
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator==(const TemplateIterator& other) const
{
    return (m_node == other.m_node);
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator!=(const TemplateIterator& other) const
{
    return (m_node != other.m_node);
}
