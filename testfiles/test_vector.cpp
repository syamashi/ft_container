#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <class T>
void vdebug(T& V) {
  cout << "size:" << V.size() << " capacity:" << V.capacity() << endl;
  cout << "{ ";
  for (typename T::iterator it = V.begin(); it != V.end(); ++it)
    cout << *it << " ";
  cout << "}" << endl;
}

static void bitout(size_t n){
  rep(i, 64){
    cout << ((n>>(63-i))&1);
    if (i%8==7) cout << " ";
  }
  cout << endl;
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

void vector_capacity_test() {
  pout("vector_capacity_test");
  int sz = 200;
  ft::vector<int> v1;

  size_t cap = v1.capacity();
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

void vector_clear_test() {
  pout("void vector_clear_test");
  ft::vector<int> container(3);  // {1, 2, 3}
  rep(i, 3) container[i] = i + 1;

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
  rep(i, 5) V2[i] = i + 1;
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
  for (int i = 0; i < 10; i++) mylist.push_back(i * 10);

  std::list<int>::iterator it = mylist.begin();

  ft::advance(it, 5);

  cout << "The sixth element in mylist is: " << *it << '\n';

  ft::advance(it, -3);

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

void traits_frontinserter() {
  std::deque<int> foo, bar;
  for (int i = 1; i <= 5; i++) {
    foo.push_back(i);
    bar.push_back(i * 10);
  }

  std::copy(bar.begin(), bar.end(), ft::front_inserter(foo));

  cout << "foo contains:";
  for (std::deque<int>::iterator it = foo.begin(); it != foo.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';
}

void traits_inserter() {
  std::list<int> foo, bar;
  for (int i = 1; i <= 5; i++) {
    foo.push_back(i);
    bar.push_back(i * 10);
  }

  std::list<int>::iterator it = foo.begin();
  advance(it, 3);

  std::copy(bar.begin(), bar.end(), ft::inserter(foo, it));

  cout << "foo contains:";
  for (std::list<int>::iterator it = foo.begin(); it != foo.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  return;
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
  pout("traits_frontinserter");
  traits_frontinserter();
  pout("traits_inserter");
  traits_inserter();
}

void rit_op_equal() {
  ft::vector<int> a1(3);
  rep(i, 3) a1[i] = i;

  // ft::reverse_iterator<ft::vector<int>::const_iterator> it1 =
  // a1.crbegin();
  ft::reverse_iterator<ft::vector<int>::const_iterator> it1 = a1.rbegin();
  ft::reverse_iterator<ft::vector<int>::iterator> it2 = a1.rbegin();
  it1 = it2;
  // it1 = a1.begin(); // no viable overloaded '='
  cout << *it2 << endl;  // 2
}

void rit_base() {
  ft::vector<int> v(6);
  rep(i, 6) v[i] = i;

  typedef ft::reverse_iterator<ft::vector<int>::iterator> RevIt;

  const ft::vector<int>::iterator it = v.begin() + 3;
  RevIt r_it(it);

  cout << "*it == " << *it << '\n'
       << "*r_it == " << *r_it << '\n'
       << "*r_it.base() == " << *r_it.base() << '\n'
       << "*(r_it.base()-1) == " << *(r_it.base() - 1) << '\n';

  RevIt r_end(v.begin());
  RevIt r_begin(v.end());

  for (ft::vector<int>::iterator itt = r_end.base(); itt != r_begin.base();
       ++itt) {
    cout << *itt << ' ';
  }
  cout << '\n';

  for (RevIt it = r_begin; it != r_end; ++it) {
    cout << *it << ' ';
  }
  cout << '\n';
}

void rit_op_ref() {
  typedef ft::reverse_iterator<ft::vector<int>::iterator> RI1;
  ft::vector<int> vi(4);
  rep(i, 4) vi[i] = i;
  RI1 r0 = vi.rbegin();
  cout << "*r0 = " << *r0 << '\n';
  *r0 = 42;
  cout << "vi[3] = " << vi[3] << '\n';

  RI1 r1 = vi.rend() - 2;
  cout << "*r1 = " << *r1 << '\n';
}

void rit_op_block() {
  {
    ft::vector<int> v(4);
    rep(i, 4) v[i] = i;
    ft::reverse_iterator<ft::vector<int>::iterator> iter;
    iter = v.rbegin();
    for (size_t i = 0; i != v.size(); ++i)
      cout << iter[i] << ' ';  // the type of iter[i] is `int&`
    cout << '\n';
  }
  return;
}

void rit_ops() {
  ft::vector<int> v;
  rep(i, 5) v.push_back(i);

  ft::vector<int>::reverse_iterator rv =
      (ft::reverse_iterator<ft::vector<int>::iterator>)v.rbegin();
  cout << *(++rv) << ' ';    // 3
  cout << *(--rv) << ' ';    // 4
  cout << *(rv + 3) << ' ';  // 1
  rv += 3;
  cout << rv[0] << ' ';  // 1
  rv -= 3;
  cout << rv[0] << '\n';  // 4
}

void rit_nonmember_ops() {
  //    int a[] {0, 1, 2, 3};
  //             |  └───── x, y
  //             └──────── z

  ft::vector<int> a(4);
  rep(i, 4) a[i] = i;
  ft::reverse_iterator<ft::vector<int>::iterator> x = a.rend() - 4;
  ft::reverse_iterator<ft::vector<int>::iterator> y = a.rend() - 4;
  ft::reverse_iterator<ft::vector<int>::iterator> z = a.rbegin() + 1;
  cout << std::boolalpha << "*x == " << *x << '\n'  // 3
       << "*y == " << *y << '\n'                    // 3
       << "*z == " << *z << '\n'                    // 2
       << "x == y ? " << (x == y) << '\n'           // true
       << "x != y ? " << (x != y) << '\n'           // false
       << "x <  y ? " << (x < y) << '\n'            // false
       << "x <= y ? " << (x <= y) << '\n'           // true
       << "x == z ? " << (x == z) << '\n'           // false
       << "x != z ? " << (x != z) << '\n'           // true
       << "x <  z ? " << (x < z) << '\n'            // true
       << "x <= z ? " << (x <= z) << '\n'           // true
      ;
}

void rit_nonmember_op_plus() {
  {
    ft::vector<int> v(4);
    rep(i, 4) v[i] = i;
    ft::reverse_iterator<ft::vector<int>::iterator> ri1;
    ri1 = v.rbegin();
    cout << *ri1 << ' ';  // 3
    ft::reverse_iterator<ft::vector<int>::iterator> ri2 = 2 + ri1;
    cout << *ri2 << ' ';  // 1
  }
}

void rit_nonmember_op_minus() {
  {
    ft::vector<int> v(4);
    rep(i, 4) v[i] = i;
    ft::reverse_iterator<ft::vector<int>::iterator> ri1, ri2;
    ri1 = v.rbegin();
    ri2 = v.rend();
    cout << (ri2 - ri1) << ' ';   // 4
    cout << (ri1 - ri2) << '\n';  // -4
  }
}

void reverse_iterator_test() {
  pout("reverse_iterator");
  ft::vector<int> V;
  rep(i, 6) V.push_back(i);
  ft::reverse_iterator<ft::vector<int>::iterator> first = V.rbegin();
  ft::reverse_iterator<ft::vector<int>::iterator> last = V.rend();

  // 54321
  for (ft::reverse_iterator<ft::vector<int>::iterator> rit = first; rit != last;
       ++rit)
    cout << *rit << " ";
  cout << endl;
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

void vector_construct_iter_iter_test() {
  pout("vector_construct_iter_iter_test");
  ft::vector<int> V(3, 5);
  vdebug(V);
  ft::vector<int> V2(V.begin(), V.end());
  vdebug(V2);
}

void vector_copy_constructer() {
  pout("vector_copy_constructer");
  ft::vector<int> V1(3, 1);
  ft::vector<int> V2(V1);
  V2 = V1;
  vdebug(V1);
  vdebug(V2);
}

void vector_assign_test() {
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

void vector_at_test() {
  pout("vector_at_test");
  ft::vector<int> data;
  rep(i, 6) data.push_back(i + 1);
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

void vector_operator_daikakko_test() {
  pout("vector_operator[]_test");
  ft::vector<int> numbers(4);
  rep(i, 4) numbers[i] = (i + 1) * 2;

  cout << "Second element: " << numbers[1] << '\n';

  numbers[0] = 5;
  vdebug(numbers);
}

void vector_front_test() {
  pout("vector_front_test");

  std::string words = "omgwtf";
  ft::vector<char> letters(6);
  rep(i, 6) letters[i] = words[i];

  if (!letters.empty()) {
    cout << "The first character is '" << letters.front() << "'.\n";
  }
}

void vector_back_test() {
  pout("vector_back_test");

  std::string words = "abcdef";
  ft::vector<char> letters(6);
  rep(i, 6) letters[i] = words[i];

  if (!letters.empty()) {
    cout << "The last character is '" << letters.back() << "'.\n";
  }
}

void vector_data_test_pointer_func(const int* p, std::size_t size) {
  cout << "data = ";
  for (std::size_t i = 0; i < size; ++i) cout << p[i] << ' ';
  cout << '\n';
}

void vector_data_test() {
  pout("vector_data_test");

  ft::vector<int> container(4);
  rep(i, 4) container[i] = i + 1;

  // Prefer container.data() over &container[0]
  vector_data_test_pointer_func(container.data(), container.size());
}

void vector_begin_test() {
  pout("vector_begin_test");

  ft::vector<int> nums(5);
  int _nums[5];
  _nums[0] = 1;
  _nums[1] = 2;
  _nums[2] = 4;
  _nums[3] = 8;
  _nums[4] = 16;
  rep(i, 5) nums[i] = _nums[i];

  ft::vector<std::string> fruits(3);
  fruits[0] = "orange";
  fruits[1] = "apple";
  fruits[2] = "raspberry";

  ft::vector<char> empty;

  // Print vector.
  vdebug(nums);

  // Sums all integers in the vector nums (if any), printing only the result.
  cout << "Sum of nums: " << std::accumulate(nums.begin(), nums.end(), 0)
       << '\n';

  // Prints the first fruit in the vector fruits, checking if there is any.
  if (!fruits.empty()) cout << "First fruit: " << *fruits.begin() << '\n';

  if (empty.begin() == empty.end()) cout << "vector 'empty' is indeed empty.\n";
}

void vector_rbegin_test() {
  pout("vector_rbegin_test");

  ft::vector<int> nums(5);
  int _nums[5];
  _nums[0] = 1;
  _nums[1] = 2;
  _nums[2] = 4;
  _nums[3] = 8;
  _nums[4] = 16;
  rep(i, 5) nums[i] = _nums[i];

  ft::vector<std::string> fruits(3);
  fruits[0] = "orange";
  fruits[1] = "apple";
  fruits[2] = "raspberry";

  ft::vector<char> empty;

  // Print vector.
  vdebug(nums);

  // Sums all integers in the vector nums (if any), printing only the result.
  cout << "Sum of nums: " << std::accumulate(nums.rbegin(), nums.rend(), 0)
       << '\n';

  // Prints the first fruit in the vector fruits, checking if there is any.
  if (!fruits.empty()) cout << "First fruit: " << *fruits.rbegin() << '\n';

  if (empty.rbegin() == empty.rend())
    cout << "vector 'empty' is indeed empty.\n";
}

void vector_empty_test() {
  pout("vector_empty_test");

  cout << std::boolalpha;
  ft::vector<int> numbers;
  cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';

  numbers.push_back(42);
  cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';
}

void vector_max_size_test() {
  pout("vector_max_size_test");

  ft::vector<char> s;
  cout << "VC:" << s.max_size() << "\n";
  bitout(s.max_size());

  ft::vector<int> v;
  cout << "VI:" << v.max_size() << "\n";
  bitout(v.max_size());
}

void vector_insert_test() {
  pout("vector_insert_test");

  ft::vector<int> vec(3, 100);
  vdebug(vec);

  ft::vector<int>::iterator it = vec.begin();
  it = vec.insert(it, 200);
  vdebug(vec);

  vec.insert(it, 2, 300);
  vdebug(vec);

  // "it" no longer valid, get a new one:
  it = vec.begin();

  ft::vector<int> vec2(2, 400);
  vec.insert(it + 2, vec2.begin(), vec2.end());
  vdebug(vec);

  int arr[3];
  arr[0] = 501;
  arr[1] = 502;
  arr[2] = 503;
  vec.insert(vec.begin(), arr, arr + 2);
  //    vec.insert(vec.end()+1, arr, arr+3); // Segmentation fault
  vdebug(vec);
}

void vector_erase_test() {
  pout("vector_erase_test");
  ft::vector<int> V0;
  //  V0.erase(V0.begin()); // segf
  V0.push_back(0);
  V0.erase(V0.begin());
  vdebug(V0);

  rep(i, 2) V0.push_back(i);
  rep(i, 2) {
    V0.erase(V0.begin() + 1 - i);
    vdebug(V0);
  }

  rep(i, 5) V0.push_back(i);
  rep(i, 3) {
    V0.erase(V0.begin() + 2);
    vdebug(V0);
  }

  ft::vector<int> c(10);
  rep(i, 10) c[i] = i;
  vdebug(c);

  c.erase(c.begin());
  vdebug(c);

  c.erase(c.begin() + 2, c.begin() + 5);
  vdebug(c);

  // Erase all even numbers (C++11 and later)
  for (ft::vector<int>::iterator it = c.begin(); it != c.end();) {
    if (*it % 2 == 0) {
      it = c.erase(it);
    } else {
      ++it;
    }
  }
  vdebug(c);

  ft::vector<int>::iterator it = c.begin();
  rep(i, 3) {
    c.erase(it);
    vdebug(c);
  }
}

void vector_pop_back_test() {
  pout("vector_pop_back_test");

  ft::vector<int> numbers;

  numbers.push_back(5);
  numbers.push_back(3);
  numbers.push_back(4);

  vdebug(numbers);
  rep(i, 3) {
    numbers.pop_back();
    vdebug(numbers);
  }
}

void vector_swap_test() {
  pout("vector_swap_test");
  ft::vector<int> a1(3), a2(2);
  rep(i, 3) a1[i] = i + 1;
  rep(i, 2) a2[i] = i + 4;

  ft::vector<int>::iterator it1 = a1.begin() + 1;
  ft::vector<int>::iterator it2 = a2.begin() + 1;

  int& ref1 = a1.front();
  int& ref2 = a2.front();

  vdebug(a1);
  vdebug(a2);
  cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << endl << endl;
  a1.swap(a2);

  vdebug(a1);
  vdebug(a2);
  cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

  a1.swap(a1);
  vdebug(a1);
  vdebug(a2);
  cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

  // Note that after swap the iterators and references stay associated with
  // their original elements, e.g. it1 that pointed to an element in 'a1' with
  // value 2 still points to the same element, though this element was moved
  // into 'a2'.
}

void vector_nonmember_operator_test() {
  pout("vector_nonmember_operator_test");

  ft::vector<int> alice(3);
  rep(i, 3) alice[i] = i + 1;
  ft::vector<int> bob(4);
  rep(i, 4) bob[i] = i + 7;
  ft::vector<int> eve(3);
  rep(i, 3) eve[i] = i + 1;

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

void vector_nonmember_swap_test() {
  pout("vector_nonmember_swap_test");

  ft::vector<int> alice(3);  // {1, 2, 3}
  rep(i, 3) alice[i] = i + 1;
  ft::vector<int> bob(4);  //{7, 8, 9, 10}
  rep(i, 4) bob[i] = i + 7;

  // Print state before swap
  cout << "alice:";
  vdebug(alice);
  cout << "\n"
          "bob  :";
  vdebug(bob);
  cout << '\n';

  cout << "-- alice.swap(bob)\n";
  alice.swap(bob);

  // Print state after swap
  cout << "alice:";
  vdebug(alice);
  cout << "\n"
          "bob  :";
  vdebug(bob);
  cout << '\n';

  cout << "-- std::swap()\n";
  std::swap(alice, bob);

  // Print state after swap
  cout << "alice:";
  vdebug(alice);
  cout << "\n"
          "bob  :";
  vdebug(bob);
  cout << '\n';
}

void vector_test() {
  alloc_test();
  traits_test();
  reverse_iterator_test();
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
}
