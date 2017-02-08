#ifndef _MICRO_ALGORITHM_H_
#define _MICRO_ALGORITHM_H_

namespace MicroSTL {
	template<class BidirectionalIterator>
	bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
		BidirectionalIterator ite = first;
		++ite;
		if( first == last || ite == last ) return false;
		ite = last;
		--ite;
		while( 1 ) {
			BidirectionalIterator iite = ite;
			--ite;
			if( *ite < *iite ) {
				BidirectionalIterator bi = last;
				while( *ite >= *bi ) --bi;
				iter_swap(ite, bi);
				reverse(iite, last);
				return true;
			}
			if( ite == first ) {
				reverse(first, last);
				return false;
			}
		}
	}

	template<class BidirectionalIterator>
	bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
		BidirectionalIterator ite = first;
		++ite;
		if (first == last || ite == last) return false;
		ite = last;
		--ite;
		while (1) {
			BidirectionalIterator iite = ite;
			--ite;
			if (*ite > *iite) {
				BidirectionalIterator bi = last;
				while (*ite <= *bi) --bi;
				iter_swap(ite, bi);
				reverse(iite, last);
				return true;
			}
			if (ite == first) {
				reverse(first, last);
				return false;
			}
		}
	}
}

#endif // !_MICRO_ALGORITHM_H_
