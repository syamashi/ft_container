#include <stdlib.h>
#include <iostream>
#include "array_iterator0826.hpp"

namespace ft
{
	template< typename T , std::size_t N >
	struct array
	{
		using value_type = T ;
		using reference = T & ;
		using const_reference = T const & ;
		using size_type = std::size_t ;
		using iterator = array_iterator<array> ;
		using const_iterator = array_const_iterator<array> ;
		std::iterator_traits<int> it;
		value_type storage[N] ;

		reference operator [] ( size_type i ) { return storage[i] ; }
		const_reference operator [] ( size_type i ) const { return storage[i] ; }
		reference front() { return storage[0] ; }
		const_reference front() const { return storage[N-1] ; }
		reference back() { return storage[0] ; }
		const_reference back() const { return storage[N-1] ; }

		size_type size() { return N ; }

		iterator begin() { return iterator( *this, 0 ) ; }
		iterator end() { return iterator( *this, N ) ; }
		const_iterator begin() const { return const_iterator( *this, 0 ) ; }
		const_iterator end() const { return const_iterator( *this, N ) ; }
		const_iterator cbegin() const { return const_iterator( *this, 0 ) ; }
		const_iterator cend() const { return const_iterator( *this, N ) ; }

		reference at( std::size_t n ){
			if ( n >= size() )
				throw std::out_of_range("Error: Out of Range") ;
			return storage[n] ;
		}

		void fill( T const & u ){
			for (size_type i = 0; i < N; ++i) storage[i] = u ;
		}

	};
}
