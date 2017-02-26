#ifndef _MICRO_ITERATOR_H_
#define _MICRO_ITERATOR_H_

#include <cstddef>

namespace MicroSTL {
	template<class I>
	struct iterator_traits {
		typedef typename I::iterator_category	iterator_category;
		typedef typename I::value_type			value_type;
		typedef typename I::difference_type		difference_type;
		typedef typename I::pointer				pointer;
		typedef typename I::reference			reference;
	};
	
	template<class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}

#endif // !_MICRO_ITERATOR_H_
