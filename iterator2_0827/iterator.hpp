#include <iostream>

namespace ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag: public input_iterator_tag { };
	struct bidirectional_iterator_tag: public forward_iterator_tag { };
	struct random_access_iterator_tag: public bidirectional_iterator_tag { };

	struct cout_iterator
	{
		using difference_type = void ;
		using value_type = void ;
		using pointer = void ;
		using reference = void ;
		using iterator_category = ft::output_iterator_tag ;

		cout_iterator & operator *() { return *this ; }
		cout_iterator & operator ++() { return *this ; }
		cout_iterator & operator ++(int) { return *this ; }

		template < typename T >
		cout_iterator & operator =( T const & x )
		{
			std::cout << x ;
			return *this ;
		}
	};

	template < typename Container >
	struct back_inserter
	{
		using difference_type = void ;
		using value_type = void ;
		using pointer = void ;
		using reference = void ;
		using iterator_category = ft::output_iterator_tag ;

		Container & c ;

		back_inserter & operator *() { return *this ; }
		back_inserter & operator ++() { return *this ; }
		back_inserter & operator ++(int) { return *this ; }

		back_inserter( Container & c ) : c(c) { }
		back_inserter & operator =( const typename Container::value_type & value )
		{
			c.push_back( value ) ;
			return *this ;
		}
	};

	template < typename T >
	struct cin_iterator
	{
		using difference_type = std::ptrdiff_t ;
		using value_type = T ;
		using reference = T & ;
		using pointer = T * ;
		using iterator_category = ft::input_iterator_tag ;

		bool fail ;
		value_type value ;

		cin_iterator( bool fail = false ): fail(fail) { ++*this ; }
		reference operator *() { return value ; }
		cin_iterator & operator ++() {
			if (!fail){
				std::cin >> value ;
				fail = std::cin.fail() ;
			}
			return *this ;
		}

		cin_iterator operator ++(int) {
			auto copy = *this ;
			++*this ;
			return copy ;
		}

		bool operator == ( cin_iterator const & r) { return fail == r.fail ; }
		bool operator != ( cin_iterator const & r) { return !(*this == r) ;}
	};

	template < typename T >
	struct iota_iterator
	{
		using difference_type = std::ptrdiff_t ;
		using value_type = T ;
		using reference = T & ;
		using pointer = T * ;
		using iterator_category = std::bidirectional_iterator_tag ;

		T value ;
		iota_iterator ( T value = 0 ) : value ( value ) { };
		reference operator *() noexcept { return value ; }
//		const reference operator *() const noexcept { return value ;}

		iota_iterator & operator ++(){
			++value;
			return *this ;
		}

		iota_iterator operator ++(int){
			iota_iterator<T> copy = *this ;
			++*this;
			return copy ;
		}

		iota_iterator & operator --(){
			--value ;
			return *this ;
		}

		iota_iterator operator --(int){
			iota_iterator copy = *this ;
			--*this ;
			return copy ;
		}

		iota_iterator operator += ( difference_type n ){
			value += n ;
			return *this ;
		}

		iota_iterator operator + ( difference_type n ){
			iota_iterator copy = *this ;
			*this += n;
			return copy ;
		}

		iota_iterator operator -= ( difference_type n ){
			value -= n;
			return *this ;
		}

		iota_iterator operator - ( difference_type n ){
			iota_iterator copy = *this ;
			*this -= n ;
			return copy ;
		}
		bool operator == ( iota_iterator const & i ) const noexcept { return value == i.value ; }
		bool operator != ( iota_iterator const & i ) const noexcept { return !(*this == i) ; }

		bool operator < ( iota_iterator const & i ) const noexcept { return value < i.value ; }
		bool operator <= ( iota_iterator const & i ) const noexcept { return value <= i.value ; }
		bool operator > ( iota_iterator const & i ) const noexcept { return value > i.value ; }
		bool operator >= ( iota_iterator const & i ) const noexcept { return value >= i.value ; }
	};

	// 最初の引数をTで受けたいから外に書くしかない
	template < typename T >
	iota_iterator<T> operator + ( typename iota_iterator<T>::difference_type n, iota_iterator<T> & i )
	{ return i + n ; }

	template < typename T >
	iota_iterator<T> operator - ( typename iota_iterator<T>::difference_type n, iota_iterator<T> & i )
	{ return i - n ; }



	template < typename T >
	struct forward_link_list
	{
		T value ;
		forward_link_list * next ;
	} ;

	template < typename T >
	struct link_iterator
	{
		using difference_type = std::ptrdiff_t ;
		using value_type = T ;
		using reference = T & ;
		using pointer = T * ;
		using iterator_category = std::forward_iterator_tag ;

		forward_link_list<T> *ptr ;

		link_iterator( ft::forward_link_list<T> *list) : ptr(list) { } ;

		T & operator *() noexcept { return ptr->value ; }
		link_iterator & operator ++() noexcept {
			ptr = ptr->next ;
			return *this ;
		}
		link_iterator operator ++(int) noexcept {
			link_iterator copy = *this ;
			++*this ;
			return copy ;
		}
		bool operator == ( link_iterator const & i ) const noexcept { return ptr == i.ptr ; }
		bool operator != ( link_iterator const & i ) const noexcept { return !(*this == i) ; }
	};

	template < typename iterator >
	struct iterator_traits
	{
		using difference_type = typename iterator::difference_type ;
		using value_type = typename iterator::value_type ;
		using pointer = typename iterator::pointer ;
		using reference = typename iterator::reference ;
		using iterator_category = typename iterator::iterator_category ;
	};
}
