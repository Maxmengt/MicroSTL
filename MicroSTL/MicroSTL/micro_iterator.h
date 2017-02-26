#ifndef _MICRO_ITERATOR_H_
#define _MICRO_ITERATOR_H_

namespace MicroSTL {
	template<class I>
	struct iterator_traits {
		typedef typename I::value_type value_type;
	};
	
	template<class T>
	struct iterator_traits<T*> {
		typedef T value_type;
	};
}

#endif // !_MICRO_ITERATOR_H_
