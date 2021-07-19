#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>

namespace ft{
	template < typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public :
	    // value_typeなどネストされた型名
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

	    // コンストラクター
	    vector( std::size_t n = 0, Allocator a = Allocator() ) ;
	    // デストラクター
	    ~vector() ;
	    // コピー
	    vector( const vector & x ) ;
	    vector & operator =( const vector & x ) ;

	    // 要素アクセス
	    void push_back( const T & x ) ;
	    T & operator []( std::size_t i ) noexcept ;

	    // イテレーターアクセス
	    //iterator begin() noexcept ;
	    //iterator end() noexcept ;
		iterator begin() noexcept
		{ return first ; }
		iterator end() noexcept
		{ return last ; }
	private :
	    // データメンバー
	    // 先頭の要素へのポインター
	    pointer first ;
	    // 最後の要素の1つ前方のポインター
	    pointer last ;
	    // 確保したストレージの終端
	    pointer reserved_last ;
	    // アロケーターの値
	    allocator_type alloc ;
	} ;
}
#endif
