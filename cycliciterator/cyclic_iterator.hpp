/* CyclicIterator from C++ snippets
 * Cyclic iterator for STL containers.
 * @author Kacper Kołodziej
 * @url http://kacperkolodziej.com/
 * @github https://github.com/kolodziej/cppsnippets
*/

#ifndef CYCLIC_ITERATOR_HPP
#define CYCLIC_ITERATOR_HPP
#include <iostream>
#include <iterator>

template <typename Container>
using ContainerValueType = typename Container::value_type;
template <typename Container>
using ContainerIterator = typename Container::iterator;

template <typename Container, typename T = ContainerValueType<Container>, typename Iterator = ContainerIterator<Container>>
class CyclicIterator :
	public std::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t>
{
private:
	Container& container_;
	Iterator cursor_;

public:
	CyclicIterator(Container& c) :
		container_(c),
		cursor_(c.begin())
	{}

	bool operator==(const CyclicIterator& it)
	{
		return cursor_ == it.cursor_;
	}

	bool operator!=(const CyclicIterator& it)
	{
		return !(cursor_ == it.cursor_);
	}

	T& operator*()
	{
		return *cursor_;
	}

	CyclicIterator& operator++()
	{
		++cursor_;
		if (cursor_ == container_.end())
		{
			cursor_ = container_.begin();
		}
		return *this;
	}

	CyclicIterator operator++(int)
	{
		CyclicIterator it = *this;
		++(*this);
		return it;
	}

	CyclicIterator& operator--()
	{
		if (cursor_ == container_.begin())
		{
			cursor_ = container_.end();
		}
		--cursor_;
		return *this;
	}

	CyclicIterator operator--(int)
	{
		CyclicIterator it = *this;
		--(*this);
		return it;
	}

	CyclicIterator& operator+(int n)
	{
		for (int i = 0; i < n; ++i, ++(*this));
		return *this;
	}

	CyclicIterator& operator-(int n)
	{
		for (int i = 0; i < n; ++i, --(*this));
		return *this;
	}

};

#endif
