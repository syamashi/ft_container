#if TEST  // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <list>         // std::list
#include <vector>
#include <iterator>
namespace ft = std;
#else
#include "vector.hpp"
#include "iterator.hpp"
#include <map>
#include <stack>
#include <list>         // std::list
#endif

#define rep(i, n) for (int i = 0; i < n; ++i)
#include <stdlib.h>
// iterator_traits example
#include <iostream>  // cout
#include <iterator>  // std::iterator_traits
#include <typeinfo>  // typeid
#include <algorithm>    // std::copy
#include <cstddef> // size_t

#define cout std::cout
#define endl std::endl

template <typename T>
void pout(T s) {
  static int no;
  cout << endl
            << "--- "
            << "[" << ++no << "]:" << s << " ---" << endl;
}

template <typename T>
void vdebug(T &V) {
  cout << endl << "V(" << V.size() << ") = { ";
  for (auto it = V.begin(); it != V.end(); ++it) cout << *it << " ";
  cout << "}" << endl;
}

template < typename Iterator >
void itdebug( Iterator first, Iterator last )
{
	cout << "{";
    for ( auto iter = first ; iter != last ; ++iter ){
		if(iter != first) cout << " ";
        cout << *iter ;
	}
	cout << "}" << endl;
}

void alloc_test() {
  pout("alloc_test");

  std::allocator<int> alloc;
  ft::vector<int> v1(alloc);
  vdebug(v1);
  ft::vector<int> v2(5, alloc);
  vdebug(v2);
  ft::vector<int> v3(5, 123, alloc);
  vdebug(v3);
  ft::vector<int> v4(v3);
  v4[0] = 100;
  vdebug(v4);
  vdebug(v3);
  ft::vector<int> v5;
  v5 = v3;
  vdebug(v5);
}

void reserve_test() {
  pout("reserve_test");

  ft::vector<int> V;
  rep(i, 5) V.push_back(i);
  vdebug(V);
  cout << "pre V.size:" << V.size() << " V.cap:" << V.capacity()
            << endl;
  V.reserve(3);
  vdebug(V);
  cout << "aft V.size:" << V.size() << " V.cap:" << V.capacity()
            << endl;

  ft::vector<int> V2;
  vdebug(V2);
  cout << "pre V2.size:" << V2.size() << " V2.cap:" << V2.capacity()
            << endl;
  V2.reserve(10000);
  vdebug(V2);
  cout << "aft V2.size:" << V2.size() << " V2.cap:" << V2.capacity()
            << endl;

  ft::vector<int> V3;
  rep(i, 3) V3.push_back(i);
  vdebug(V3);
  cout << "pre V3.size:" << V3.size() << " V3.cap:" << V3.capacity()
            << endl;
  V3.reserve(10000);
  vdebug(V3);
  cout << "aft V3.size:" << V3.size() << " V3.cap:" << V3.capacity()
            << endl;
}

void resize_test() {
  pout("resize_test");

  ft::vector<int> V;
  vdebug(V);
  V.resize(5);
  vdebug(V);
  V.resize(10, 10);
  vdebug(V);
  V.resize(1, 10);
  vdebug(V);
}

template <class BidirIt>
void traits_reverse(BidirIt first, BidirIt last) {
  typename ft::iterator_traits<BidirIt>::difference_type n =
      ft::distance(first, last);
  for (--n; n > 0; n -= 2) {
    typename ft::iterator_traits<BidirIt>::value_type tmp = *first;
    *first++ = *--last;
    *last = tmp;
  }
}

void traits_advance() {
  std::list<int> mylist;
  for (int i=0; i<10; i++) mylist.push_back (i*10);

  std::list<int>::iterator it = mylist.begin();

  ft::advance (it,5);

  cout << "The sixth element in mylist is: " << *it << '\n';

  ft::advance (it,-3);

  cout << "The three element in mylist is: " << *it << '\n';
}

void traits_backinserter() {
  ft::vector<int> foo, bar;
  for (int i = 1; i <= 5; i++) {
    foo.push_back(i);
    bar.push_back(i * 10);
  }

  std::copy(bar.begin(), bar.end(), ft::back_inserter(foo));

  cout << "foo contains:";
  for (ft::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';
}

void traits_frontinserter(){
  std::deque<int> foo,bar;
  for (int i=1; i<=5; i++)
  { foo.push_back(i); bar.push_back(i*10); }

  std::copy (bar.begin(),bar.end(),ft::front_inserter(foo));

  cout << "foo contains:";
  for ( std::deque<int>::iterator it = foo.begin(); it!= foo.end(); ++it )
	  cout << ' ' << *it;
  cout << '\n';
}

void traits_inserter(){
  std::list<int> foo,bar;
  for (int i=1; i<=5; i++)
  { foo.push_back(i); bar.push_back(i*10); }

  std::list<int>::iterator it = foo.begin();
  advance (it,3);

  std::copy (bar.begin(),bar.end(),ft::inserter(foo, it));

  cout << "foo contains:";
  for ( std::list<int>::iterator it = foo.begin(); it!= foo.end(); ++it )
	  cout << ' ' << *it;
  cout << '\n';

  return ;
}

void traits_test() {
  ft::vector<int> V;
  rep(i, 5) V.push_back(i);
  pout("traits_reverse");
  traits_reverse(V.begin(), V.end());
  vdebug(V);
  pout("traits_advance");
  traits_advance();
  pout("traits_backinserter");
  traits_backinserter();
  pout("traits_frontinserter") ;
  traits_frontinserter();
  pout("traits_inserter");
  traits_inserter();
}

void rit_op_equal(){
	ft::vector<int> a1(3);
	rep(i, 3) a1[i] = i;

	ft::reverse_iterator<ft::vector<int>::const_iterator> it1 = a1.crbegin();
	auto it2 = a1.rbegin();
	it1 = it2;
	// it1 = a1.begin(); // no viable overloaded '='
	cout << *it2 << endl; // 2
}

void rit_base(){
    ft::vector<int> v(6);
	rep(i, 6) v[i] = i;
 
    using RevIt = ft::reverse_iterator<ft::vector<int>::iterator>;
 
    const auto it = v.begin() + 3;
    RevIt r_it{it};
 
    cout << "*it == " << *it << '\n'
              << "*r_it == " << *r_it << '\n'
              << "*r_it.base() == " << *r_it.base() << '\n'
              << "*(r_it.base()-1) == " << *(r_it.base() - 1) << '\n';

    RevIt r_end{v.begin()};
    RevIt r_begin{v.end()};
 
    for (auto it = r_end.base(); it != r_begin.base(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
 
    for (auto it = r_begin; it != r_end; ++it) {
        cout << *it << ' ';
    }
    cout << '\n';
}

void rit_op_ref(){
/*
    using RI0 = ft::reverse_iterator<int*>;
    int a[] { 0, 1, 2, 3 };
    RI0 r0 { std::rbegin(a) };
    cout << "*r0 = " << *r0 << '\n';
    *r0 = 42;
    cout << "a[3] = " << a[3] << '\n';
*/ 
    using RI1 = ft::reverse_iterator<ft::vector<int>::iterator>;
    ft::vector<int> vi(4);
	rep(i, 4) vi[i] = i;
	RI1 r0 = vi.rbegin();
    cout << "*r0 = " << *r0 << '\n';
    *r0 = 42;
    cout << "vi[3] = " << vi[3] << '\n';

    RI1 r1 { vi.rend() - 2 };
    cout << "*r1 = " << *r1 << '\n';
 
/*    using RI2 = std::reverse_iterator<std::vector<std::complex<double>>::iterator>; // nomember name complex
    std::vector<std::complex<double>> vc { {1,2}, {3,4}, {5,6}, {7,8} };
    RI2 r2 { vc.rbegin() + 1 };
    cout << "vc[2] = " << "(" << r2->real() << "," << r2->imag() << ")\n";	
*/
}

void rit_op_block(){

/*    {
        int a[]{0, 1, 2, 3};
        ft::reverse_iterator<int*> iter;
		iter = a.rbegin();
        for (size_t i{}; i != sizeof(a)/sizeof(a[0]); ++i)
            cout << iter[i] << ' '; // the type of iter[i] is `int&`
        cout << '\n';
    }
*/   {
        ft::vector<int> v(4);
		rep(i, 4) v[i] = i;
        ft::reverse_iterator<ft::vector<int>::iterator> iter;
		iter = v.rbegin();
        for (size_t i{}; i != v.size(); ++i)
            cout << iter[i] << ' '; // the type of iter[i] is `int&`
        cout << '\n';
    }
/*  {
        // constexpr context
        constexpr static std::array<int, 4> z{0, 1, 2, 3};
        constexpr std::reverse_iterator<decltype(z)::const_iterator> it{std::crbegin(z)};
        static_assert(it[1] == 2);
    }
    {
        std::list<int> li{0, 1, 2, 3};
        ft::reverse_iterator<std::list<int>::iterator> iter;
		iter = li.rbegin();
        *iter = 42; // OK
    //  iter[0] = 13; // compilation error ~ the underlying iterator
                      // does not model the random access iterator
    }
	*/
	return ;
}

void rit_ops(){
    ft::vector<int> v;
	rep(i, 5) v.push_back(i);

    auto rv = ft::reverse_iterator< ft::vector<int>::iterator > {v.rbegin()};
    cout << *(++rv) << ' '; // 3
    cout << *(--rv) << ' '; // 4
    cout << *(rv + 3) << ' '; // 1
    rv += 3;
    cout << rv[0] << ' '; // 1
    rv -= 3;
    cout << rv[0] << '\n'; // 4

/* 
    std::list<int> l {5, 6, 7, 8};
    auto rl = ft::reverse_iterator< std::list<int>::iterator > {l.rbegin()};
    cout << *(++rl) << ' '; // OK: 3
    cout << *(--rl) << ' ' << endl; // OK: 4
    // The following statements raise compilation error because the
    // underlying iterator does not model the random access iterator:
//  *(rl + 3) = 13;
//  rl += 3;
//  rl -= 3;
*/
}

void rit_nonmember_ops(){

//    int a[] {0, 1, 2, 3};
    //             ↑  └───── x, y
    //             └──────── z
 
	ft::vector<int> a(4);
	rep(i, 4) a[i] = i;
    ft::reverse_iterator<ft::vector<int>::iterator> x = a.rend() - 4;
    ft::reverse_iterator<ft::vector<int>::iterator> y = a.rend() - 4;
    ft::reverse_iterator<ft::vector<int>::iterator> z = a.rbegin() + 1;
    cout
        << std::boolalpha
        << "*x == " << *x << '\n' // 3
        << "*y == " << *y << '\n' // 3
        << "*z == " << *z << '\n' // 2
        << "x == y ? " << (x == y) << '\n' // true
        << "x != y ? " << (x != y) << '\n' // false
        << "x <  y ? " << (x <  y) << '\n' // false
        << "x <= y ? " << (x <= y) << '\n' // true
        << "x == z ? " << (x == z) << '\n' // false
        << "x != z ? " << (x != z) << '\n' // true
        << "x <  z ? " << (x <  z) << '\n' // true!
        << "x <= z ? " << (x <= z) << '\n' // true
/*
        << "x <=> y == 0 ? " << (x <=> y == 0) << '\n' // true
        << "x <=> y <  0 ? " << (x <=> y <  0) << '\n' // false
        << "x <=> y >  0 ? " << (x <=> y >  0) << '\n' // false
        << "x <=> z == 0 ? " << (x <=> z == 0) << '\n' // false
        << "x <=> z <  0 ? " << (x <=> z <  0) << '\n' // true
        << "x <=> z >  0 ? " << (x <=> z >  0) << '\n' // false
*/
        ;
}

void rit_nonmember_op_plus(){
    {
        ft::vector<int> v(4);
		rep(i, 4) v[i] = i;
        ft::reverse_iterator<ft::vector<int>::iterator> ri1;
		ri1 = v.rbegin() ;
        cout << *ri1 << ' '; // 3
        ft::reverse_iterator<ft::vector<int>::iterator> ri2 { 2 + ri1 };
        cout << *ri2 << ' '; // 1
    }
/*    {
        std::list l {5, 6, 7, 8};
        ft::reverse_iterator<std::list<int>::iterator>
            ri1{ ft::reverse_iterator{ l.rbegin() } };
        cout << *ri1 << '\n'; // 8
    //  auto ri2 { 2 + ri1 }; // error: the underlying iterator does
                              // not model the random access iterator
    }
*/
}

void rit_nonmember_op_minus()
{
    {
        ft::vector<int> v(4);
		rep(i, 4) v[i] = i;
        ft::reverse_iterator<ft::vector<int>::iterator> ri1, ri2;
		ri1 = v.rbegin();
		ri2 = v.rend();
        cout << (ri2 - ri1) << ' '; // 4
        cout << (ri1 - ri2) << '\n'; // -4
    }
/*
    {
        std::list l {5, 6, 7, 8};
        ft::reverse_iterator<std::list<int>::iterator>
            ri1{ ft::reverse_iterator{ l.rbegin() } },
            ri2{ std::reverse_iterator{ l.rend()   } };
    //  auto n = (ri1 - ri2); // error: the underlying iterators do not
                              // model the random access iterators
    }	
*/
}

void reverse_iterator_test(){
	pout("reverse_iterator");
    ft::vector<int> V;
    rep(i, 6) V.push_back(i);
    // std::reverse_iterator< std::vector<int>::iterator >
    ft::reverse_iterator< ft::vector<int>::iterator > first = V.rbegin() ;
    ft::reverse_iterator< ft::vector<int>::iterator > last = V.rend() ;

    // 54321
	itdebug(first, last);
	pout("rit_operator=");
	rit_op_equal();
	pout("rit_base");
	rit_base();
	pout("rit_op_ref");
	rit_op_ref();
	pout("rit_op_block");
	rit_op_block();
	pout("rit_ops");
	rit_ops();
	pout("rit_nonmember_ops");
	rit_nonmember_ops();
	pout("rit_nonmember_op_plus");
	rit_nonmember_op_plus();
	pout("rit_nonmember_op_minus");
	rit_nonmember_op_minus();
}

int main() {
  alloc_test();
  reserve_test();
  resize_test();
  traits_test();
  reverse_iterator_test();
}
