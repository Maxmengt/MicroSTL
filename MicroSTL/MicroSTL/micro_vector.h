#ifndef _MICRO_VECTOR_H
#define _MICRO_VECTOR_H

#include <memory>
#include "micro_allocator.h"

namespace MicroSTL {
	template<class T, class Alloc = Allocator<T>>
	class Vector {
	public:
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type*		iterator;
		typedef value_type&		reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;
		typedef Alloc			data_allocator;

		Vector() : begin_(0), end_(0), end_of_storage_(0) {}
		Vector(size_type size);
		Vector(size_type size, const value_type& value);
		~Vector();

		iterator begin() const { return begin_; }
		iterator end() const { return end_; }

		size_type size() const { return size_type(end_ - begin_); }
		size_type capacity() const { return size_type(end_of_storage_ - begin_); }

		reference operator[](size_type n) const { return *(begin_ + n); }
		reference front() const { return *begin_; }
		reference back() const { return *(end_ - 1); }

		void push_back(const size_type& value);
		void pop_back();
	private:
		iterator begin_;
		iterator end_;
		iterator end_of_storage_;


	};
}

#endif // !_MICRO_VECTOR_H
