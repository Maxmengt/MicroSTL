#ifndef _MICRO_TYPE_TRAITS_H_
#define _MICRO_TYPE_TRAITS_H_

namespace MicroSTL {
	struct __true_type {};
	struct __false_type {};

	template<class type>
	struct __type_traits {
		typedef __true_type		this_dummy_member_must_be_first;
		typedef __false_type	has_trivial_default_constructor;
		typedef __false_type	has_trivial_copy_constructor;
		typedef __false_type	has_trivial_assignment_operator;
		typedef __false_type	has_trivial_destructor;
		typedef __false_type	is_POD_type;
	};
}

#endif // !_MICRO_TYPE_TRAITS_H_
