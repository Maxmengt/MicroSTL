#ifndef _MICRO_VECTOR_H
#define _MICRO_VECTOR_H

#include <memory>
#include <algorithm>
#include "micro_allocator.h"

namespace MicroSTL {
	template<class T, class Alloc = Allocator<T>>
	class Vector {
	public:
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type*			iterator;
		typedef const value_type*	const_iterator;
		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;

		Vector() : begin_(0), end_(0), end_of_storage_(0) {}
		Vector(size_type size);
		Vector(size_type size, const value_type& value);
		~Vector();
		
		// The copy assignment copies all the elements from x into the container (with x preserving its contents).
		inline Vector<T>& operator=(const Vector<T>& x);

		iterator begin() const { return begin_; }
		iterator end() const { return end_; }

		size_type size() const { return size_type(end_ - begin_); }
		size_type capacity() const { return size_type(end_of_storage_ - begin_); }

		reference operator[](size_type n) const { return *(begin_ + n); }
		reference front() const { return *begin_; }
		reference back() const { return *(end_ - 1); }

		void push_back(const value_type& value);
		void pop_back();
		iterator insert(iterator position, const value_type& value);
		iterator insert(iterator position, size_type n, const value_type& value);
		template<class InputIterator>
		iterator insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(const_iterator position);
		iterator erase(const_iterator first, const_iterator last);
		void clear() { erase(begin_, end_); };
	private:
		iterator begin_;
		iterator end_;
		iterator end_of_storage_;

		void allocateFill(size_type size, const value_type& value);
	};

	template<class T, class Alloc>
	Vector<T, Alloc>::Vector(size_type size) {
		allocateFill(size, T());
	}

	template<class T, class Alloc>
	Vector<T, Alloc>::Vector(size_type size, const value_type& value) {
		allocateFill(size, value);
	}

	template<class T, class Alloc>
	Vector<T, Alloc>::~Vector() {
		if( !capacity() ) return ;
		allocator_type::destroy(begin_, end_);
		allocator_type::deallocate(begin_, size());
	}

	template<class T, class Alloc>
	inline Vector<T>& Vector<T, Alloc>::operator=(const Vector<T>& x) {
		for( size_t i = 0; i < x.size(); ++ i ) {
			(*this).push_back(x[i]);
		}
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::push_back(const value_type& value) {
		insert(end(), value);
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::pop_back() {
		--end_;
		allocator_type::destroy(end_);
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator position, const value_type& value) {
		if( end_ != end_of_storage_ ) {
			allocator_type::construct(end_);
			++end_;
			std::copy_backward(position, end_ - 1, end_);
			*position = value;
		}
		else {
			const size_type old_size = size();
			const size_type new_size = old_size > 0 ? (old_size << 1) : 1;
			
			iterator new_begin = allocator_type::allocate(new_size);
			iterator new_end = new_begin;
			iterator new_position = 0;

			try {
				new_end = std::uninitialized_copy(begin_, position, new_begin);
				allocator_type::construct(new_end, value);
				new_position = new_end;
				++new_end;
				new_end = std::uninitialized_copy(position, end_, new_end);
			}
			catch( ... ) {
				allocator_type::destroy(new_begin, new_end);
				allocator_type::deallocate(new_begin, new_size);
				throw;
			}

			allocator_type::destroy(begin_, end_);
			allocator_type::deallocate(begin_, old_size);

			begin_ = new_begin;
			end_ = new_end;
			end_of_storage_ = begin_ + new_size;
			position = new_position;
		}
		return position;
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator position, size_type n, const value_type& value) {
		if( !n ) return position; 
		difference_type storageLeft = end_of_storage_ - end_;
		if( (size_t)storageLeft >= n ) {
			iterator last = end_ + n, last_ = end_;
			while(last_ != position ) {
				allocator_type::construct(--last, *(--last_));
			}
			while(last_ != last ) {
				*(last_++) = value;
			}
			end_ += n;
		}
		else {
			size_t old_size = size();
			size_t new_size = old_size + std::max(old_size, n);
			iterator new_begin = allocator_type::allocate(new_size);
			iterator new_end = new_begin;
			iterator new_position = 0;
			try {
				new_end = std::uninitialized_copy(begin_, position, new_begin);
				new_position = new_end;
				new_end = std::uninitialized_fill_n(new_end, n, value);
				new_end = std::uninitialized_copy(position, end_, new_end);
			}
			catch( ... ) {
				allocator_type::destroy(new_begin, new_end);
				allocator_type::deallocate(new_begin, new_size);
				throw;
			}
			allocator_type::destroy(begin_, end_);
			allocator_type::deallocate(begin_, old_size);
			begin_ = new_begin;
			end_ = new_end;
			end_of_storage_ = begin_ + new_size;
			position = new_position;
		}
		return position;
	}

	template<class T, class Alloc>
	template<class InputIterator>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last) 
	{

		return position;
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(const_iterator position) {
		return erase(position, position + 1);
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(const_iterator first, const_iterator last) {
		difference_type lenOfTail = end_ - last;
		iterator first_ = (iterator)first;
		iterator last_ = (iterator)last;
		iterator new_position = first_;
		while( lenOfTail -- ) {
			*(first_++) = *(last_++);
		}
		end_ = first_;
		while( first_ != last_ ) {
			allocator_type::destroy(first_++);
		}
		return new_position;
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::allocateFill(size_type size, const value_type& value) {
		begin_ = allocator_type::allocate(size);
		std::uninitialized_fill_n(begin_, size, value);
		end_of_storage_ = end_ = begin_ + size;
	}



}

#endif // !_MICRO_VECTOR_H
