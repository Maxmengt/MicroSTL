#ifndef _MICRO_CONSTRUCT_H_
#define _MICRO_CONSTRUCT_H_

#include <new>

namespace MicroSTL {
	/**
	 * Construct an object in existing memory by invoking an allocated
	 * object's constructor with an initializer.
	 */
	template<class T1, class T2>
	inline void construct(T1* place_address, const T2& value) {
		/* new (place_address) type (initializers) */
		new (place_address) T1(value);
	}

	template<class T>
	inline void construct(T* place_address) {
		new (place_address) T();
	}

	/**
	 * Destroy the object pointed to by a pointer type.
	 */
	template<class T>
	inline void destroy(T* obj) {
		obj->~T();
	}

	/**
	 * Destroy a range of objects. If the value_type of the object has 
	 * a trivial destructor, the compiler should optimize all of this 
	 * away, otherwise the objects' destructors must be invoked.
	 */
	template<class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last) {
		// typedef typename __type_traits<*>::has_trivial_destructor has_trivial_destructor;
		_destroy(first, last, has_trivial_destructor());
	}

	/**
	 * If the value_type of the object has a trivial destructor,
	 * then do nothing.
	 */
	template<class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, __true_type) {}

	/**
	 * If the value_type of the object has a non-trivial destructor,
	 * then invoke the objects' destructors.
	 */
	template<class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, __false_type) {
		for ( ; first != last; ++ first ) {
			destroy(&*first);
		}
	}
}

#endif // !_MICRO_CONSTRUCT_H_