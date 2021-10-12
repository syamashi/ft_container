#if TEST //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map>
	#include <stack>
	#include <vector>
	#include "iterator.hpp"
#endif

#include <stdlib.h>
// iterator_traits example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator_traits
#include <typeinfo>     // typeid

template < typename T >
void pout(T s){
	std::cout << std::endl << "--- " << s << " ---" << std::endl;
}

template < typename Container >
void back_inserter_test( Container const & c )
{
	pout("back_inserter_test");

	std::vector< typename Container::value_type > temp ;
	auto out = ft::back_inserter<Container>(temp);
	std::copy( std::begin(c), std::end(c), out );
	for(auto t: temp) std::cout << t;
	std::cout << std::endl;
}

void cin_iterater_test()
{
	pout("cin_iterator");
	ft::cin_iterator<int> input, fail(true) ;
	std::vector<int> buffer ;
	std::copy( input, fail, ft::back_inserter<std::vector<int>>(buffer) ) ;
	for(auto v: buffer){
		std::cout << v;
	}
	std::cout << std::endl;
}

void iota_iterator_test(){
	pout("iota_iterator");
	ft::iota_iterator<int> iter(0);
	std::cout << *iter;
	std::cout << *++iter;
	std::cout << *iter++;
	std::cout << *iter;

	ft::iota_iterator<int> first(0), last(10);
	for(auto it = first; it != last; ++it){
		std::cout << *it ;
	}
	std::cout << std::endl;
	for(auto it = first; it != last; it += 2){
		std::cout << *it ;
	}
	std::cout << std::endl;
	for(auto it = first; it != last; it = it + 2){
		std::cout << *it ;
	}
	std::cout << std::endl;
	for(auto it = first; it != last; it = 2 + it){
		std::cout << *it ;
	}
	std::cout << std::endl;

//	std::for_each( first, last, [](auto i ) { std::cout << i ; } ) ;

//	std::vector<int> v ;
//	std::copy( first, last, std::back_inserter(v)) ;
}


template < typename ForwardIterator >
void forward_multi( ForwardIterator first, ForwardIterator last )
{
    using vector_type = std::vector< typename ForwardIterator::value_type > ;

    // 全要素の値をv1にコピー
    vector_type v1 ;
    for ( auto iter = first ; iter != last ; ++iter )
        v1.push_back( *iter ) ;

    // 全要素の値をv2にコピー
    // イテレーターがもう一度使われる
    vector_type v2 ;
    for ( auto iter = first ; iter != last ; ++iter )
        v2.push_back( *iter ) ;

    // マルチパス保証があれば常にtrue
    bool b = v1 == v2 ;
	pout("v1");
	for(auto v: v1) std::cout << v ;
	pout("v2");
	for(auto v: v2) std::cout << v ;
	std::cout << std::endl << "bool:" << b << std::endl;
}

void forward_link_test()
{
	pout("forward_link_iterator");
    ft::forward_link_list<int> list3{ 3, nullptr } ;
    ft::forward_link_list<int> list2{ 2, &list3 } ;
    ft::forward_link_list<int> list1{ 1, &list2 } ;
    ft::forward_link_list<int> list0{ 0, &list1 } ;
	ft::link_iterator<int> it(&list0), end(&list3);
	forward_multi(it, end);
}

int main()
{
    std::vector<int> v = {1,2,3,4,5} ;
    ft::cout_iterator out ;

    std::copy( std::begin(v), std::end(v), out ) ;


	back_inserter_test(v);
	cin_iterater_test();
	iota_iterator_test();
	forward_link_test();
}
