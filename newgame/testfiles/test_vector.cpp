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

void vector_construct_test() {
  pout("vector_construct_test");

  std::allocator<int> alloc;
  ft::vector<int> v0;
  vdebug(v0);

  ft::vector<int> v1(alloc);
  vdebug(v1);
  //  ft::vector<int> v2(5, alloc); // c++14
  //  vdebug(v2);

  ft::vector<int> v3(5, 123, alloc);
  vdebug(v3);

  ft::vector<int> v4(v3.begin() + 1, v3.end());
  vdebug(v4);

  ft::vector<int> v5(v3);
  v5[0] = 100;
  vdebug(v5);
}

void vector_copy_construct_test() {
  pout("vector_copy_constructer_test");

  ft::vector<int> V1(3, 1);
  ft::vector<int> V2(V1);
  ft::vector<int> V3;
  ft::vector<int> V4(10, 42);
  vdebug(V1);
  vdebug(V2);
  V3 = V2;
  vdebug(V3);
  V4 = V2;
  vdebug(V4);
}

void vector_assign_test() {
  pout("vector_assign_test");
  ft::vector<char> characters;
  characters.assign(5, 'a');
  vdebug(characters);

  const std::string extra(6, 'b');
  characters.assign(extra.begin(), extra.end());
  vdebug(characters);

  characters.assign(3, 'c');
  vdebug(characters);

  characters.assign(0, 'd');
  vdebug(characters);

  characters.assign(10, 'e');
  vdebug(characters);
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
  vector_construct_test();
  vector_copy_construct_test();
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
