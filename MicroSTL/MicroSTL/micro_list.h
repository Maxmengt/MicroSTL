#ifndef _MICRO_LIST_H_
#define _MICRO_LIST_H_

#include "micro_allocator.h"

namespace MicroSTL {
	template<class T>
	struct listNode {
		typedef listNode<T>* pointer;
		pointer prev;
		pointer next;
		T data;
	};

	template<class T>
	struct listIterator {
		typedef listIterator<T>		iterator;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
		typedef listNode<T>*		link_type;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
	
		link_type node;

		// constructor
		listIterator() {}
		listIterator(link_type nodePointer) : node(nodePointer) {}
		listIterator(const iterator& ite) : node(ite.node) {}

		// operator overload
		bool operator==(const iterator& _Right) const { return node == _Right.node; }
		bool operator!=(const iterator& _Right) const { return node != _Right.node; }

		reference operator*() const { return (*node).data; }

		iterator& operator++() {
			node = (*node).next;
			return *this;
		}
		iterator& operator++(int) {
			iterator old = node;
			node = (*node).next;
			return old;
		}

		iterator& operator--() {
			node = (*node).prev;
			return *this;
		}
		iterator& operator--(int) {
			iterator old = node;
			node = (*node).prev;
			return old;
		}
	};

	template<class T, class Alloc=Allocator<T>>
	class list {
	public:
		typedef listIterator<T>		iterator;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
		typedef listNode<T>*		link_type;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
	
		iterator begin() const { return (*node).next; }
		iterator end() const { return node;  }

		bool empty() const { return (*node).next == node; }
		size_type size() const {
			std::distance
		}
	protected:
		link_type node;
		
	};
}

#endif // !_MICRO_LIST_H_

