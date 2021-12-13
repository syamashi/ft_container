#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <typename T>
void vdebug(T &V) {
	cout << "size:" << V.size() << " capacity:" << V.capacity() << endl;
	cout << "{ ";
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
//  ft::vector<int> v2(5, alloc); // c++14
//  vdebug(v2);
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

void vector_reserve_test() {
  pout("vector_reserve_test");

  ft::vector<int> V;
  rep(i, 5) V.push_back(i);
  vdebug(V);
  V.reserve(3);
  vdebug(V);
  ft::vector<int> V2;
  vdebug(V2);
  V2.reserve(10000);
  vdebug(V2);

  ft::vector<int> V3;
  rep(i, 3) V3.push_back(i);
  vdebug(V3);
  V3.reserve(10000);
  vdebug(V3);
}

void vector_capacity_test()
{
	pout("vector_capacity_test");
    int sz = 200;
    ft::vector<int> v1;
 
    auto cap = v1.capacity();
    cout << "initial capacity=" << cap << '\n';
 
    for (int n = 0; n < sz; ++n) {
        v1.push_back(n);
        if (cap != v1.capacity()) {
            cap = v1.capacity();
            cout << "new capacity=" << cap << '\n';
        }
    }
 
    cout << "final size=" << v1.size() << '\n';
    cout << "final capacity=" << v1.capacity() << '\n';
}

void vector_clear_test()
{
	pout("void vector_clear_test");
    ft::vector<int> container(3) ; // {1, 2, 3}
	rep(i, 3) container[i] = i+1;
 
    cout << "Before clear:";
	vdebug(container);
 
    cout << "Clear\n";
    container.clear();
 
    cout << "After clear:";
    vdebug(container);
}

void vector_resize_test() {
  pout("vector_resize_test");

  ft::vector<int> V;
  vdebug(V);
  V.resize(5);
  vdebug(V);
  V.resize(10, 10);
  vdebug(V);
  V.resize(1, 10);
  vdebug(V);

  ft::vector<int> V2(5);
  rep(i, 5) V2[i] = i+1;
  vdebug(V2);
  V2.resize(10);
  vdebug(V2);
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

//	ft::reverse_iterator<ft::vector<int>::const_iterator> it1 = a1.crbegin();
	ft::reverse_iterator<ft::vector<int>::const_iterator> it1 = a1.rbegin();
	ft::reverse_iterator<ft::vector<int>::iterator> it2 = a1.rbegin();
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
        << "x <  z ? " << (x <  z) << '\n' // true
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

class integral_test_A {};
enum integral_test_E : int {};
template <class T>
T integral_test_f(T i)
{
   static_assert(std::is_integral<T>::value, "Integral required.");
   return i;
}

void is_integral_test(){

	pout("is_integral_test");
	static_assert(ft::is_integral<int>::value == true, "value == true, int is integral");
	static_assert(ft::is_same<ft::is_integral<int>::value_type, bool>::value, "value_type == bool");
	static_assert(ft::is_same<ft::is_integral<int>::type, ft::true_type>::value, "type == true_type");
	static_assert(ft::is_integral<int>() == true, "is_integral<int>() == true");

	static_assert(ft::is_integral<int*>::value == false, "value == false, int* is not integral");
	static_assert(ft::is_same<ft::is_integral<int*>::value_type, bool>::value, "value_type == bool");
	static_assert(ft::is_same<ft::is_integral<int*>::type, ft::false_type>::value, "type == false_type");
	static_assert(ft::is_integral<int*>() == false, "is_integral<int*>() == false");

	static_assert(ft::is_integral<bool>::value == true, "bool is integral");
	static_assert(ft::is_integral<char>::value == true, "char is integral");
	static_assert(ft::is_integral<char32_t>::value == true, "char32_t is integral");
	static_assert(ft::is_integral<const long long>::value == true, "const long long is integral");
	static_assert(ft::is_integral<volatile unsigned>::value == true, "volatile unsigned is integral");

	enum my_enum{};
	static_assert(ft::is_integral<my_enum>::value == false, "my_enum is not integral");
	static_assert(ft::is_integral<int&>::value == false, "int& is not integral");
	static_assert(ft::is_integral<int[1]>::value == false, "int[1] is not integral");
	static_assert(ft::is_integral<int ()>::value == false, "int () is not integral");
	static_assert(ft::is_integral<float>::value == false, "float is not integral");


	static_assert(ft::is_integral<bool>::value == true, "bool is integral");
	static_assert(ft::is_integral<char>::value == true, "char is integral");
//	static_assert(ft::is_integral<char8_t>::value == true, "bool is integral"); c++20
	static_assert(ft::is_integral<char16_t>::value == true, "char16 is integral");
	static_assert(ft::is_integral<char32_t>::value == true, "char32 is integral");
	static_assert(ft::is_integral<wchar_t>::value == true, "wchar is integral");
	static_assert(ft::is_integral<short>::value == true, "short is integral");
	static_assert(ft::is_integral<int>::value == true, "int is integral");
	static_assert(ft::is_integral<long>::value == true, "long is integral");
	static_assert(ft::is_integral<long long>::value == true, "longlong is integral");
	
	static_assert(ft::is_integral<ft::vector<int>::iterator>::value == false, "V.end() is not integral");
}

void   vector_construct_iter_iter_test()
{
	pout("vector_construct_iter_iter_test");
	ft::vector<int> V(3, 5);
	vdebug(V);
	ft::vector<int> V2(V.begin(), V.end());
	vdebug(V2);
}

void   vector_copy_constructer()
{
	pout("vector_copy_constructer");
	ft::vector<int> V1(3, 1);
	ft::vector<int> V2(V1);
	V2 = V1;
	vdebug(V1);
	vdebug(V2);
}

void vector_assign_test()
{
	pout("vector_assign_test");
    ft::vector<char> characters;
    characters.assign(5, 'a');
	vdebug(characters);
 
    const std::string extra(6, 'b');
    characters.assign(extra.begin(), extra.end());
	vdebug(characters);

//    characters.assign(extra.end(), extra.begin()); / bad_alloc

    characters.assign(3, 'c');
	vdebug(characters);

    characters.assign(0, 'd');
	vdebug(characters);

    characters.assign(10, 'e');
	vdebug(characters);

//    characters.assign({'C', '+', '+', '1', '1'}); c++11
//    print_vector();
}

void vector_at_test()
{
	pout("vector_at_test");
    ft::vector<int> data;
	rep(i, 6) data.push_back(i+1);
	data.at(2) = 4;
	cout << "test data init 1,2,4,4,5,6" << endl;
	vdebug(data);
    // Set element 1
    data.at(1) = 88;

    // Read element 2
    cout << "Element at index 2 has value " << data.at(2) << '\n';
    try {
        // Set element 6
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        cerr << exc.what() << '\n';
    }

    // Print final values
	vdebug(data);
}

void   vector_operator_daikakko_test()
{
	pout("vector_operator[]_test");
    ft::vector<int> numbers(4);
	rep(i, 4) numbers[i] = (i+1)*2;

    cout << "Second element: " << numbers[1] << '\n';
 
    numbers[0] = 5;
	vdebug(numbers);
}

void   vector_front_test()
{
	pout("vector_front_test");

	std::string words = "omgwtf";
    ft::vector<char> letters(6);
	rep(i, 6) letters[i] = words[i];
 
    if (!letters.empty()) {
        cout << "The first character is '" << letters.front() << "'.\n";
    }
}

void   vector_back_test()
{
	pout("vector_back_test");

	std::string words = "abcdef";
    ft::vector<char> letters(6);
	rep(i, 6) letters[i] = words[i];
 
    if (!letters.empty()) {
        cout << "The last character is '" << letters.back() << "'.\n";
    }
}

void vector_data_test_pointer_func(const int* p, std::size_t size)
{
    cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        cout << p[i] << ' ';
    cout << '\n';
}

/* c++20
void vector_data_test_span_func(std::span<const int> data) // since C++20
{
    cout << "data = ";
    for (const int e : data)
        cout << e << ' ';
    cout << '\n';
}
*/

void   vector_data_test()
{
	pout("vector_data_test");

    ft::vector<int> container(4);
	rep(i, 4) container[i] = i+1;
 
    // Prefer container.data() over &container[0]
    vector_data_test_pointer_func(container.data(), container.size());
 
    // std::span (C++20) is a safer alternative to separated pointer/size.
//    vector_data_test_span_func({container.data(), container.size()});
}

void   vector_begin_test()
{
	pout("vector_begin_test");

    ft::vector<int> nums(5);
	int _nums[5] = {1, 2, 4, 8, 16};
	rep(i, 5) nums[i] = _nums[i];

    ft::vector<std::string> fruits(3);
	fruits[0] = "orange";
	fruits[1] = "apple";
	fruits[2] = "raspberry";

    ft::vector<char> empty;

    // Print vector.
    std::for_each(nums.begin(), nums.end(), [](const int n) { cout << n << ' '; });
    cout << '\n';

    // Sums all integers in the vector nums (if any), printing only the result.
    cout << "Sum of nums: "
              << std::accumulate(nums.begin(), nums.end(), 0) << '\n';
 
    // Prints the first fruit in the vector fruits, checking if there is any.
    if (!fruits.empty())
        cout << "First fruit: " << *fruits.begin() << '\n';
 
    if (empty.begin() == empty.end())
        cout << "vector 'empty' is indeed empty.\n";
}

void vector_rbegin_test()
{
	pout("vector_rbegin_test");

    ft::vector<int> nums(5);
	int _nums[5] = {1, 2, 4, 8, 16};
	rep(i, 5) nums[i] = _nums[i];

    ft::vector<std::string> fruits(3);
	fruits[0] = "orange";
	fruits[1] = "apple";
	fruits[2] = "raspberry";

    ft::vector<char> empty;
 
    // Print vector.
    std::for_each(nums.rbegin(), nums.rend(), [](const int n) { cout << n << ' '; });
    cout << '\n';
 
    // Sums all integers in the vector nums (if any), printing only the result.
    cout << "Sum of nums: "
              << std::accumulate(nums.rbegin(), nums.rend(), 0) << '\n';
 
    // Prints the first fruit in the vector fruits, checking if there is any.
    if (!fruits.empty())
        cout << "First fruit: " << *fruits.rbegin() << '\n';
 
    if (empty.rbegin() == empty.rend())
        cout << "vector 'empty' is indeed empty.\n";
}

void vector_empty_test()
{
	pout("vector_empty_test");

    cout << std::boolalpha;
    ft::vector<int> numbers;
    cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';
 
    numbers.push_back(42);
    cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';
}

void vector_max_size_test()
{
	pout("vector_max_size_test");

    ft::vector<char> s;
    cout << "Maximum size of a 'vector' is " << s.max_size() << "\n";

    ft::vector<int> v;
    cout << "Maximum size of a 'vector' is " << v.max_size() << "\n";

}

void vector_insert_test()
{
	pout("vector_insert_test");

    ft::vector<int> vec(3,100);
	vdebug(vec);

    auto it = vec.begin();
    it = vec.insert(it, 200);
    vdebug(vec);

    vec.insert(it,2,300);
    vdebug(vec);

//    vec.insert(it,-2,300); // std::length_error

    // "it" no longer valid, get a new one:
    it = vec.begin();

    ft::vector<int> vec2(2,400);
    vec.insert(it+2, vec2.begin(), vec2.end());
    vdebug(vec);

    int arr[] = { 501,502,503 };
    vec.insert(vec.begin(), arr, arr+2);
//    vec.insert(vec.end()+1, arr, arr+3); // Segmentation fault
    vdebug(vec);

//  vec.insert(vec.begin(), arr+1, arr); // 'std::length_error'
}

void vector_erase_test()
{
	pout("vector_erase_test");
    ft::vector<int> c(10);
	rep(i, 10) c[i] = i;
	vdebug(c);

    c.erase(c.begin());
	vdebug(c);

    c.erase(c.begin()+2, c.begin()+5);
	vdebug(c);

    // Erase all even numbers (C++11 and later)
    for (auto it = c.begin(); it != c.end(); ) {
        if (*it % 2 == 0) {
            it = c.erase(it);
        } else {
            ++it;
        }
    }
	vdebug(c);

	auto it = c.begin();
	rep(i, 3){
		c.erase(it);
		vdebug(c);
	}
}

void   vector_pop_back_test()
{
	pout("vector_pop_back_test");

    ft::vector<int> numbers;
 
    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);
 
	vdebug(numbers);
	rep(i, 3){
	    numbers.pop_back();
		vdebug(numbers);
	}
}

void vector_swap_test()
{
	pout("vector_swap_test");
    ft::vector<int> a1(3), a2(2);
	rep(i, 3) a1[i] = i+1;
	rep(i, 2) a2[i] = i+4;
 
    auto it1 = a1.begin() + 1;
    auto it2 = a2.begin() + 1;
 
    int& ref1 = a1.front();
    int& ref2 = a2.front();
 
    vdebug(a1);
	vdebug(a2);
	cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << endl << endl ;
    a1.swap(a2);

    vdebug(a1);
	vdebug(a2);
	cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

	a1.swap(a1);
    vdebug(a1);
	vdebug(a2);
	cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'.
}

void vector_nonmember_operator_test()
{
	pout("vector_nonmember_operator_test");

    ft::vector<int> alice(3);
	rep(i, 3) alice[i] = i+1;
    ft::vector<int> bob(4);
	rep(i, 4) bob[i] = i+7;
    ft::vector<int> eve(3);
	rep(i, 3) eve[i] = i+1;
 
    cout << std::boolalpha;
 
    // Compare non equal containers
    cout << "alice == bob returns " << (alice == bob) << '\n';
    cout << "alice != bob returns " << (alice != bob) << '\n';
    cout << "alice <  bob returns " << (alice < bob) << '\n';
    cout << "alice <= bob returns " << (alice <= bob) << '\n';
    cout << "alice >  bob returns " << (alice > bob) << '\n';
    cout << "alice >= bob returns " << (alice >= bob) << '\n';
 
    cout << '\n';
 
    // Compare equal containers
    cout << "alice == eve returns " << (alice == eve) << '\n';
    cout << "alice != eve returns " << (alice != eve) << '\n';
    cout << "alice <  eve returns " << (alice < eve) << '\n';
    cout << "alice <= eve returns " << (alice <= eve) << '\n';
    cout << "alice >  eve returns " << (alice > eve) << '\n';
    cout << "alice >= eve returns " << (alice >= eve) << '\n';
}

void   vector_nonmember_swap_test()
{
	pout("vector_nonmember_swap_test");

    ft::vector<int> alice(3); // {1, 2, 3}
	rep(i, 3) alice[i] = i+1;
    ft::vector<int> bob(4); //{7, 8, 9, 10}
	rep(i, 4) bob[i] = i+7;

    // Print state before swap
    cout << "alice:";
	vdebug(alice);
    cout << "\n" "bob  :";
	vdebug(bob);
    cout << '\n';
 
    cout << "-- SWAP\n";
    ft::swap(alice, bob);
 
    // Print state after swap
    cout << "alice:";
	vdebug(alice);
    cout << "\n" "bob  :";
	vdebug(bob);
    cout << '\n';
}

void  vector_const_iterator_test()
{
	ft::vector<int> v1;
	decltype(v1)::const_iterator it = v1.begin();
}


void vector_test() {
  alloc_test();
  traits_test();
  reverse_iterator_test();
  is_integral_test();
  vector_construct_iter_iter_test();
  vector_copy_constructer();
  vector_assign_test();
  vector_at_test();
  vector_operator_daikakko_test();
  vector_front_test();
  vector_back_test();
  vector_data_test();
  vector_begin_test();
  vector_rbegin_test();
  vector_empty_test();
  vector_max_size_test();
  vector_reserve_test();
  vector_capacity_test();
  vector_clear_test();
  vector_insert_test();
  vector_erase_test();
  vector_pop_back_test();
  vector_resize_test();
  vector_swap_test();
  vector_nonmember_operator_test();
  vector_nonmember_swap_test();
  vector_const_iterator_test();
}
