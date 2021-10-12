namespace ft
{
	template < typename Array > // containerが渡されると思う
	struct array_iterator
	{
		Array & a;
		std::size_t i;

		array_iterator( Array & a , std::size_t i ) : a(a), i(i) { }

		array_iterator & operator ++()
		{
			++i;
			return *this ;
		}
		array_iterator operator ++(int)
		{
			array_iterator copy = *this;
			++*this;
			return *this;
		}
		array_iterator & operator --()
		{
			--i;
			return *this ;
		}
		array_iterator operator --(int)
		{
			array_iterator copy = *this;
			--*this;
			return *this ;
		}
		array_iterator operator +=( std::size_t n ){
			i += n;
			return *this;
		}
		array_iterator operator +( std::size_t n ) const {
			auto copy = *this;
			copy += n ;
			return copy;
		}
		array_iterator operator -=( std::size_t n ){
			i -= n;
			return *this;
		}
		array_iterator operator -( std::size_t n ) const {
			auto copy = *this;
			copy -= n ;
			return copy;
		}
		typename Array::reference operator *() { return a[i] ; }
		bool operator ==( array_iterator const & right ) { return i == right.i ; }
		bool operator !=( array_iterator const & right ) { return !( i == right.i ) ; }
		bool operator <( array_iterator const & right ) const { return i < right.i ; }
		bool operator <=( array_iterator const & right ) const { return i <= right.i ; }
		bool operator >( array_iterator const & right ) const { return i > right.i ; }
		bool operator >=( array_iterator const & right ) const { return i >= right.i ; }
		typename Array::iterator operator = ( array_iterator const & right ){
			this->a = right.a;
			this->i = right.i;
			return *this ;
		}
		typename Array::reference operator [] ( std::size_t n ) const { return *( *this + n ) ; }
	};

	template < typename Array >
	struct array_const_iterator
	{
		Array const & a ;
		std::size_t i ;

		array_const_iterator( Array const & a, std::size_t i ) : a(a), i(i) {}
		array_const_iterator( typename Array::iterator const & iter ) : a(iter.a), i(iter.i) {}

	};

}