namespace ft
{
	// 明示的なデストラクター呼び出しをする関数テンプレート
	template < typename T >
	void destroy_at( T * location )
	{
	    location->~T() ;
	}

	template < typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public :
			using value_type = T;
			using pointer = T *;
			using const_pointer = const pointer;
			using reference = value_type & ;
			using const_reference = const value_type &;

			using allocator_type = Allocator ;

			using iterator                  = pointer ;
			using const_iterator            = const_pointer ;
			using reverse_iterator          = std::reverse_iterator<iterator> ;
			using const_reverse_iterator    = std::reverse_iterator<const_iterator> ;

			using size_type = std::size_t ;

			vector( std::size_t n = 0, Allocator a = Allocator() );
			~vector();
			vector( const vector & x) ;
			vector & operator =( const vector & x);

			void push_back(const T & x) ;
			T & operator []( std::size_t i ) noexcept ;

			iterator begin() noexcept {return first ;}
			iterator begin() const noexcept {return first ;}
			iterator end() noexcept {return last ;}
			iterator end() const noexcept {return last ;}
			const_iterator cbegin() const noexcept { return first ; }
			const_iterator cend() const noexcept { return last ;}
			reverse_iterator rbegin() noexcept { return reverse_iterator{ last } ;}
			reverse_iterator rend() noexcept { return reverse_iterator{ first } ;}
			reverse_iterator crbegin() const noexcept { return reverse_iterator{ last } ;}
			reverse_iterator crend() const noexcept { return reverse_iterator{ first } ;}

			size_type size() const noexcept { return end() - begin() ;}
			bool empty() const noexcept { return begin() == end() ; };
			size_type capacity() const noexcept { return reserved_last - first ; };

//			reference operator []( size_type i ) noexcept { return first[i] ; }
			const_reference operator []( size_type i ) const { return first[i] ; }
			reference at( size_type i )
			{
				if ( i >= size() )
					throw std::out_of_range( "index is out of range." ) ;
				return first[i] ;
			}
			const_reference at( size_type i ) const
			{
				if ( i >= size() )
					throw std::out_of_range( "index is out of range." ) ;
				return first[i] ;
			}

			reference front() { return first ; }
			const_reference front() const { return first ; }
			reference back() { return last - 1 ; }
			const_reference back() const { return last - 1 ; }
		private :
		    // 先頭の要素へのポインター
		    pointer first ;
		    // 最後の要素の1つ前方のポインター
		    pointer last ;
		    // 確保したストレージの終端
		    pointer reserved_last ;
		    // アロケーターの値
		    allocator_type alloc ;
	};
}
