#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include <iostream>
//#include <iterator>
#include "scope_exit.hpp"
#include "random_access_iterator.hpp"

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

			/*
			**  std::allocator<int> alloc ;
			**	ft::vector<int> v1( alloc ) ;
			**	ft::vector<int> v2( 5, alloc );
			**	ft::vector<int> v3( 5, 123, alloc );
			*/

			vector( const allocator_type & alloc ) : first(nullptr), last(nullptr), reserved_last(nullptr), alloc(alloc) { }
			vector() : vector( allocator_type() ) { }
			vector( size_type size, const allocator_type & alloc = allocator_type() ) : vector( alloc ) { resize( size ) ; }
			vector( size_type size, const_reference value, const allocator_type & alloc = allocator_type() ) : vector( alloc ) { resize( size, value ) ; }

			template< class InputIt >
			vector( InputIt first, InputIt last,
        	const Allocator& alloc = Allocator() ) {}

									  // vector( const allocator_type & alloc )が呼ばれる
			vector( const vector & r ) : vector( traits::select_on_container_copy_construction( r.alloc ) )
			{
				reserve( r.size() ) ;

				pointer dest = first;
				for( iterator src = r.begin(), last = r.end() ; src != last ; ++dest, ++src){
					construct( dest, *src ) ;
				}
				last = first + r.size();
			}
			~vector() {
				clear() ;
				deallocate() ;
			};
			vector & operator =( const vector & r ){
				if ( this == &r ) return *this ;
				if ( size() == r.size() ){
					std::copy( r.begin(), r.end(), begin() ) ;
				}
				else{
					if (capacity() >= r.size()){
						std::copy( r.begin(), r.begin() + r.size(), begin() ) ;
						for(auto src_iter = r.begin() + r.size(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last ){
							construct( last, *src_iter ) ;
						}
					}
					else{
						destroy_until( rbegin() );
						reserve( r.size() );
						for ( auto src_iter = r.begin(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last ){
//							construct( dest_iter, *src_iter ) ;
							construct( last, *src_iter ) ;
						}
					}
				}
				return *this;
			} ;

			iterator begin() noexcept { return first ; }
			iterator end() noexcept { return last ; }
			iterator begin() const noexcept { return first ; }
			iterator end() const noexcept { return last ; }
			const_iterator cbegin() const noexcept { return first ; }
			const_iterator cend() const noexcept { return last ; }
			reverse_iterator rbegin() noexcept { return reverse_iterator{ last } ; }
			reverse_iterator rend() noexcept { return reverse_iterator{ first } ; }
			const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator{ last } ; }
			const_reverse_iterator crend() const noexcept { return const_reverse_iterator{ first } ; }

			size_type size() const { return end() - begin() ; }
			bool empty() const { return begin() == end(); }
			size_type capacity() const { return reserved_last - first ; }

			reference operator []( size_type i ) { return first[i] ; }
			const_reference operator []( size_type i ) const { return first[i] ; }

			reference at( size_type i ){
				if ( i >= size() )
					throw std::out_of_range( "index is out of range." ) ;
				return first[i] ;
			}
			const_reference at( size_type i ) const {
				if (i >= size() )
					throw std::out_of_range( "index is out of range." ) ;
				return first[i] ;
			}
			reference front() { return first ; }
			const_reference front() const { return first ; }
			reference back() { return last - 1 ; }
			const_reference back() const { return last - 1 ; }

			pointer data() { return first ;}
			const_pointer data() const { return first ; }

			void reserve( size_type sz ){
//				std::cout << "[reserve] sz:" << sz << " capacity():" << capacity() << std::endl;
				if ( sz <= capacity() ) return ;

				// 新しく領域をとって、コピーする
				pointer ptr = allocate( sz ) ;
				pointer old_first = first ;
				pointer old_last = last ;
				size_type old_capacity = capacity();

				first = ptr ;
				last = first ;
				reserved_last = first + sz ;

				for ( auto old_iter = old_first; old_iter != old_last; ++old_iter, ++last ){
					construct( last, std::move(*old_iter) ) ;
				}

				for ( auto riter = reverse_iterator(old_last), rend = reverse_iterator(old_first) ; riter != rend; ++riter ){
					destroy( &*riter ) ;
				}
				traits::deallocate( alloc, old_first, old_capacity ) ;
			}

			void resize( size_type sz ){
				std::cout << "[resize] sz:" << sz << " size():" << size() << std::endl;
				if (sz < size() ){
					auto diff = size() - sz ;
					destroy_until( rbegin() + diff ) ;
					last = first + sz ;
				}
				else if ( sz > size() ){
					reserve( sz );
					for( ; last != reserved_last; ++last ){
						construct ( last ) ;
					}
				}
			}

			void resize( size_type sz , const_reference value ){
				if (sz < size() ){
					auto diff = size() - sz ;
					destroy_until( rbegin() + diff ) ;
					last = first + sz ;
				}
				else if ( sz > size() ){
					reserve( sz );
					for( ; last != reserved_last; ++last ){
						construct ( last , value ) ;
					}
				}
			}

			void push_back( const_reference value ){
				std::cout << "[push_back]:" << value << std::endl;
				if ( size() + 1 > capacity()){
					auto c = size() ;
					if ( c == 0 ) c = 1;
					else c *= 2;
					reserve( c ) ;
				}
				construct( last, value ) ;
				++last ;
			}

		private :
			pointer first ;
			pointer last ;
			pointer reserved_last ;
			allocator_type alloc ;

			typedef std::allocator_traits<allocator_type> traits;
			pointer allocate( size_type n ) { return traits::allocate( alloc, n ) ; }
			void deallocate( ) { traits::deallocate( alloc, first, capacity() ) ; }
			void construct( pointer ptr ) { traits::construct( alloc, ptr ) ; }
			void construct( pointer ptr, const_reference value ) { traits::construct( alloc, ptr, value ) ; }
			void construct( pointer ptr, value_type && value ) { traits::construct( alloc, ptr, std::move(value) ) ; }
			void destroy( pointer ptr ) { traits::destroy( alloc, ptr ) ; }
			void destroy_until( reverse_iterator rend ){
				for( auto riter = rbegin() ; riter != rend ; ++riter, --last ){
					destroy( &*riter ) ;
				}
			}
			void clear() { destroy_until( rend() ) ; }
	};
}

#endif