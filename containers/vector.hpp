#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../utils/iterator.hpp"
#include <iostream>
//#include <iterator>
#include "../utils/random_access_iterator.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/algorithm.hpp"

namespace ft
{
	template < typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		typedef Allocator allocator_type ;
		public :
			typedef T value_type ;
			typedef typename allocator_type::pointer pointer ;
			typedef typename allocator_type::const_pointer const_pointer ;
			typedef typename allocator_type::reference reference ;
			typedef typename allocator_type::const_reference const_reference ;
			typedef size_t size_type ;
			typedef ptrdiff_t difference_type ;

			typedef typename ft::random_access_iterator<value_type> iterator ;
			typedef typename ft::random_access_iterator<const value_type> const_iterator ;
			typedef typename ft::reverse_iterator<iterator> reverse_iterator ;
			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator ;

			vector() : vector( allocator_type() ) { }
			explicit vector( const Allocator& alloc ) : _first(nullptr), _last(nullptr), _reserved_last(nullptr), _alloc(alloc) { }
			explicit vector( size_type count,
                 const T& value = T(),
                 const Allocator& alloc = Allocator()) : vector( alloc ) { resize( count, value ) ; }

			template< class InputIt >
			vector( InputIt head, InputIt tail,
        	const Allocator& alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr) : vector( alloc ) {
				difference_type sz = ft::distance(head, tail);
				resize( sz );
				pointer ptr = _first;
				for (InputIt src = head; src != tail; ++src, ++ptr ){
					construct ( ptr , *src ) ;
				}
			}

//			vector( const vector & other ) : vector( traits::select_on_container_copy_construction( other._alloc ) )
			vector( const vector & other ) : vector( other._alloc )
			{
				reserve( other.size() ) ;

				pointer dest = _first;
				for( const_iterator src = other.begin(), last = other.end() ; src != last ; ++dest, ++src){
					construct( dest, *src ) ;
				}
				_last = _first + other.size();
			}
			~vector() {
				clear() ;
				deallocate() ;
			};
			vector & operator =( const vector & r ){
				if ( this == &r ) return *this ;
				if ( size() == r.size() ){
					ft::copy( r.begin(), r.end(), begin() ) ;
				}
				else{
					if (capacity() >= r.size()){
						ft::copy( r.begin(), r.begin() + r.size(), begin() ) ;
						for( const_iterator src_iter = r.begin() + r.size(), src_end = r.end(); src_iter != src_end; ++src_iter, ++_last ){
							construct( _last, *src_iter ) ;
						}
					}
					else{
						destroy_until( rbegin() );
						reserve( r.size() );
						for ( const_iterator src_iter = r.begin(), src_end = r.end(); src_iter != src_end; ++src_iter, ++_last ){
//							construct( dest_iter, *src_iter ) ;
							construct( _last, *src_iter ) ;
						}
					}
				}
				return *this;
			} ;

			iterator begin() { return _first ; }
			const_iterator begin() const { return _first ; }
			iterator end() { return _last ; }
			const_iterator end() const { return _last ; }
			reverse_iterator rbegin() { return reverse_iterator{ end() } ; }
			const_reverse_iterator rbegin() const { return reverse_iterator{ end() } ; }
			reverse_iterator rend() { return reverse_iterator{ _first } ; }
			const_reverse_iterator rend() const { return reverse_iterator{ _first } ; }

			size_type size() const { return end() - begin() ; }
			bool empty() const { return begin() == end(); }
			size_type capacity() const { return _reserved_last - _first ; }

			reference operator []( size_type i ) { return _first[i] ; }
			const_reference operator []( size_type i ) const { return _first[i] ; }

			reference at( size_type i ){
				if ( i >= size() )
					throw std::out_of_range( "index is out of range." ) ;
				return _first[i] ;
			}
			const_reference at( size_type i ) const {
				if (i >= size() )
					throw std::out_of_range( "index is out of range." ) ;
				return _first[i] ;
			}
			reference front() { return _first ; }
			const_reference front() const { return _first ; }
			reference back() { return _last - 1 ; }
			const_reference back() const { return _last - 1 ; }

			pointer data() { return _first ;}
			const_pointer data() const { return _first ; }

			void reserve( size_type sz ){
				if ( sz <= capacity() ) return ;

				// 新しく領域をとって、コピーする
				pointer ptr = allocate( sz ) ;
				pointer old_first = _first ;
				pointer old_last = _last ;
				size_type old_capacity = capacity();

				_first = ptr ;
				_last = _first ;
				_reserved_last = _first + sz ;

				for ( pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++_last ){
//					construct( _last, std::move(*old_iter) ) ; c++11
					construct( _last, *old_iter ) ;
				}

				for ( reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first) ; riter != rend; ++riter ){
					destroy( &*riter ) ;
				}
				_alloc.deallocate( old_first, old_capacity ) ;
			}

			void resize( size_type sz ){
				if ( sz < size() ){
					size_type diff = size() - sz ;
					destroy_until( rbegin() + diff ) ;
					_last = _first + sz ;
				}
				else if ( sz > size() ){
					reserve( sz );
					for( ; _last != _reserved_last; ++_last ){
						construct ( _last ) ;
					}
				}
			}

			void resize( size_type sz , const_reference value ){
				if ( sz < size() ){
					size_type diff = size() - sz ;
					destroy_until( rbegin() + diff ) ;
					_last = _first + sz ;
				}
				else if ( sz > size() ){
					reserve( sz );
					for( ; _last != _reserved_last; ++_last ){
						construct ( _last , value ) ;
					}
				}
			}

			void push_back( const_reference value ){
				if ( size() + 1 > capacity()){
					size_type c = size() ;
					if ( c == 0 ) c = 1;
					else c *= 2;
					reserve( c ) ;
				}
				construct( _last, value ) ;
				++_last ;
			}

		private :
			pointer _first ;
			pointer _last ;
			pointer _reserved_last ;
			allocator_type _alloc ;

//			typedef std::allocator_traits<allocator_type> traits;
			pointer allocate( size_type n ) { return _alloc.allocate(n) ; }
			void deallocate( ) { _alloc.deallocate( _first, capacity() ) ; }
			void construct( pointer ptr ) { _alloc.construct( ptr ) ; }
			void construct( pointer ptr, const_reference value ) { _alloc.construct( ptr, value ) ; }
//			void construct( pointer ptr, value_type && value ) { traits::construct( _alloc, ptr, std::move(value) ) ; } c++11
			void destroy( pointer ptr ) { _alloc.destroy( ptr ) ; }
			void destroy_until( reverse_iterator rend ){
				for( reverse_iterator riter = rbegin() ; riter != rend ; ++riter, --_last ){
					destroy( &*riter ) ;
				}
			}
			void clear() { destroy_until( rend() ) ; }
	};
}

#endif