#ifndef _MICRO_ALLOCATOR_H
#define _MICRO_ALLOCATOR_H

#include "micro_alloc.h"

namespace Micro_STL {
	template<class T>
	class Allocator {
	public:
		static T* allocate();
		static T* allocate(size_t n);
		static void deallocate(T* place_address);
		static void deallocate(T* place_address, size_t n);
		
		static void construct(T* place_address);
		static void construct(T* place_address, const T& value);
		static void destroy(T* obj);
		static void destroy(T* first, T* last);
	};

	template<class T>
	T* Allocator<T>::allocate() {
		return Alloc::allocate(sizeof(T));
	}
	
	template<class T>
	T* Allocator<T>::allocate(size_t n) {
		return Alloc::allocate(sizeof(T) * n);
	}

	template<class T>
	void Allocator<T>::deallocate(T* place_address) {
		Alloc::deallocate(place_address);
	}

	template<class T>
	void Allocator<T>::deallocate(T* place_address, size_t n) {
		Alloc::deallocate(place_address, sizeof(T) * n);
	}

	template<class T>
	void Allocator<T>::construct(T* place_address) {
		new (place_address) T();
	}

	template<class T>
	void Allocator<T>::construct(T* place_address, const T& value) {
		new (place_address) T(value);
	}

	template<class T>
	void Allocator<T>::destroy(T* obj) {
		obj->~T();
	}

	template<class T>
	void Allocator<T>::destroy(T* first, T* last) {
		// has_trivial_destructor ?
		for( ; first != last; ++ first ) {
			first->~T();
		}
	}
}

#endif // !_MICRO_ALLOCATOR_H
