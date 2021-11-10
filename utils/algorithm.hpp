#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

	template< class InputIt, class OutputIt >
	OutputIt copy( InputIt first, InputIt last, OutputIt d_first )
	{
		while ( first != last )
			*d_first++ = *first++ ;
		return d_first;
	}

	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		for ( ; first1 != last1; ++first1, ++first2)
		    if (!bool(*first1 == *first2))
				return false;
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
	{
		for ( ; first1 != last1; ++first1, ++first2)
			if (!bool(p(*first1, *first2)))
				return false;
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
	                             InputIt2 first2, InputIt2 last2)
	{
	    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
	        if (*first1 < *first2) return true;
	        if (*first2 < *first1) return false;
	    }
	    return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
	{
	    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
	        if (comp(*first1, *first2)) return true;
	        if (comp(*first2, *first1)) return false;
	    }
	    return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt, class UnaryFunction>
	constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
	{
	    for (; first != last; ++first) {
	        f(*first);
	    }
	    return f; // implicit move since C++11
	}
};  // namespace ft

#endif