#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <class Con>
void sdebug(Con const& S) {
  cout << "size:" << S.size() << endl;

  for (auto it = S.begin(); it != S.end(); ++it) {
    cout << "S[" << *it << "]" << endl;
  }
  cout << endl;
}

template <typename Iterator>
void itdebug(Iterator first, Iterator last) {
  cout << "{";
  for (auto iter = first; iter != last; ++iter) {
    if (iter != first) cout << " ";
    cout << *iter;
  }
  cout << "}" << endl;
}

void set_insert_test() {
  pout("set_insert_test");

  ft::set<int> S;
  rep(i, 20) {
    int key = 0 - i;
    cout << "--- S.insert(" << key << ") ---" << endl;
    std::pair<ft::set<int>::iterator, bool> ret = S.insert(key);
    cout << " size:" << S.size() << endl;
    cout << " ret:" << *ret.first << endl;
  }
}

/*
void set_insert_delete_hardtest(){
        // 開始地点を20か所ずらして、連番で作成
        ft::set<int> S;
  int N=20;
  rep(i, N){ // start
    rep(j, N){
      int k=(i+j)%N;
                S.insert(k);
                S.debug2();
    }
        rep(j, N+10){
      int k=(i+j)%N;
      S.erase(k);
      S.debug2();
        }
  }
}
*/

void set_operator_equal_test() {
  pout("set_operator_equal_test");

  ft::set<int> nums1;

  rep(i, 10) { nums1.insert(i); }
  ft::set<int> nums2;

  cout << "Initially:\n";
  cout << "---nums1---" << endl;
  sdebug(nums1);
  cout << "---nums2---" << endl;
  sdebug(nums2);

  // copy assignment copies data from nums1 to nums2
  nums2 = nums1;

  cout << "After assigment:\n";
  cout << "---nums1---" << endl;
  sdebug(nums1);
  cout << "---nums2---" << endl;
  sdebug(nums2);
}

void set_all_erase_test() {
  pout("set_all_erase_test");
  ft::set<int> S;
  int N = 5;
  rep(i, N) {  // start
    rep(j, N) {
      int k = (i + j) % N;
      S.insert(k);
    }
    cout << "ins:" << i << endl;
    sdebug(S);
    rep(j, N + 10) {
      int k = (i + j) % N;
      S.erase(k);
    }
    cout << "ers:" << i << endl;
    sdebug(S);
  }
}

void set_get_alloc_test() {
  pout("set_get_alloc_test");

  ft::set<int> S;
  ft::set<int>::allocator_type al = S.get_allocator();
  int* p = al.allocate(1);
  int q = 1;
  al.construct(p, q);
  cout << *p << endl;
  al.deallocate(p, 1);
}

void set_insert_iterator_test() {
  pout("set_insert_iterator_test");

  ft::set<int> S;
  rep(i, 10) S.insert(i * 2);
  ft::set<int>::iterator ret;

  cout << "---S.insert(S.end(), 4)---" << endl;
  ret = S.insert(S.end(), 4);
  cout << "ret:" << *ret << endl;
  sdebug(S);
  cout << "---S.insert(S.begin(), 4)---" << endl;
  ret = S.insert(S.begin(), 4);
  cout << "ret:" << *ret << endl;
  sdebug(S);
  cout << "---S.insert(S.end(), 5)---" << endl;
  ret = S.insert(S.end(), 5);
  cout << "ret:" << *ret << endl;
  sdebug(S);
  cout << "---S.insert(S.begin(), 7)---" << endl;
  ret = S.insert(S.begin(), 7);
  cout << "ret:" << *ret << endl;
  sdebug(S);
}

void set_insert_iterator_iterator_test() {
  pout("set_insert_iterator_iterator_test");
  ft::set<int> S;
  ft::set<int> SS;
  rep(i, 10) S.insert(i * 2);
  rep(i, 10) SS.insert(i * 2 + 1);

  S.insert(SS.begin(), SS.end());
  sdebug(S);
  S.insert(SS.begin(), SS.end());
  sdebug(S);
}

struct Point_begin_test {
  double x, y;
};

// Compare the x-coordinates of two Point pointers
struct PointCmp_begin_test {
  bool operator()(const Point_begin_test* lhs,
                  const Point_begin_test* rhs) const {
    return lhs->x < rhs->x;
  }
};

template <class Con>
void begin_test_out(Con& mag) {
  // Update and print the magnitude of each node
  for (typename Con::iterator iter =
           mag.begin();
       iter != mag.end(); ++iter) {
    Point_begin_test* cur = *iter;
    double ret = std::hypot(cur->x, cur->y);  // hypot == sqrt(a,b)
    cout << "The magnitude of (" << cur->x << ", " << cur->y << ") is ";
    cout << ret << '\n';
  }
}

template <class Con>
void begin_test_const_out(const Con& mag) {
  // Update and print the magnitude of each node
  for (typename Con::const_iterator
           iter = mag.begin();
       iter != mag.end(); ++iter) {
    Point_begin_test* cur = *iter;
    double ret = std::hypot(cur->x, cur->y); // hypot == sqrt(a,b)
    cout << "The magnitude of (" << cur->x << ", " << cur->y << ") is ";
    cout << ret << '\n';
  }
}

void set_begin_test() {
  Point_begin_test points[3];
  points[0] = {2, 0};
  points[1] = {1, 0};
  points[2] = {3, 0};

  // points[].first でsortされる
  ft::set<Point_begin_test*, PointCmp_begin_test> mag;
  mag.insert(points);
  mag.insert(points+1);
  mag.insert(points+2);

  begin_test_out(mag);
  begin_test_const_out(mag);
}

template <class Con>
void set_rbegin_test_out(Con& S) {
  cout << "set_rbegin_test_out" << endl;
  for (typename Con::reverse_iterator it = S.rbegin(); it != S.rend(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

template <class Con>
void set_rbegin_test_const_out(const Con& S) {
  cout << "set_rbegin_test_const_out" << endl;
  for (typename Con::const_reverse_iterator it = S.rbegin(); it != S.rend();
       ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void set_rbegin_test() {
  pout("set_rbegin_test");

  ft::set<int> S;
  rep(i, 5) S.insert(i);

  set_rbegin_test_out(S);
  set_rbegin_test_const_out(S);
}

void set_empty_test() {
  pout("set_empty_test");

  ft::set<int> S;

  int N = 5;
  rep(i, N) {
    rep(j, i) S.insert(j);
    cout << "ins:" << S.empty() << " size:" << S.size() << endl;
    rep(j, i) {
      S.erase(j);
      cout << "ers:" << S.empty() << " size:" << S.size() << endl;
    }
  }
}

void set_max_size_test() {
  pout("set_max_size_test");

  ft::set<int> SII;
  ft::set<char> SCC;

  cout << "int:" << SII.max_size() << endl;
  cout << "char:" << SCC.max_size() << endl;
}

void set_clear_test() {
  pout("set_clear_test");

  ft::set<int> S;

  int N = 5;
  rep(i, N) {
    rep(j, i) S.insert(j - 100);
    cout << "ins:" << i << endl;
    sdebug(S);
    cout << "clear" << endl;
    S.clear();
    sdebug(S);
  }
}

void set_erase_test() {
  pout("set_erase_test");

  ft::set<int> S;
  int N = 5;

  rep(i, N) S.insert(i);
  rep(i, N * 2) {
    size_t ret = S.erase((i + 1) % N);
    cout << "erase_key:" << i << " ret:" << ret << endl;
  }

  rep(i, N) S.insert(i);
  for (ft::set<int>::iterator it = S.begin(); it != S.end();) {
    cout << "S.erase(" << *it << ")" << endl;
    S.erase(it++);
    sdebug(S);
  }

  rep(i, N) {  // 開始位置
    rep(j, N) S.insert(j);
    ft::set<int>::iterator it = S.begin();
    rep(j, i)++ it;
    cout << "S.erase(" << *S.begin() << "," << *it << ")" << endl;
    S.erase(S.begin(), it);
    sdebug(S);
    S.clear();
  }

  rep(i, N) {  // 開始位置
    rep(j, N) S.insert(j);
    ft::set<int>::iterator it = S.end();
    rep(j, i + 1)-- it;
    cout << "S.erase(" << *it << ",S.end())" << endl;
    S.erase(it, S.end());
    sdebug(S);
    S.clear();
  }
}

void set_swap_test() {
  pout("set_swap_test");

  ft::set<char> alice;
  rep(i, 3) alice.insert('a' + i);

  ft::set<char> blank;
  cout << "alice.swap(blank)" << endl;
  alice.swap(blank);
  cout << "alice" << endl;
  sdebug(alice);
  sdebug(blank);
  cout << "alice.swap(blank)" << endl;
  alice.swap(blank);
  cout << "alice" << endl;
  sdebug(alice);
  sdebug(blank);

  cout << "blank.swap(alice)" << endl;
  blank.swap(blank);
  cout << "alice" << endl;
  sdebug(alice);
  sdebug(blank);
  cout << "blank.swap(alice)" << endl;
  blank.swap(blank);
  cout << "alice" << endl;
  sdebug(alice);
  sdebug(blank);

  cout << "std::swap(alice, blank)" << endl;
  std::swap(alice, blank);
  cout << "alice" << endl;
  sdebug(alice);
  sdebug(blank);
  cout << "std::swap(alice, blank)" << endl;
  std::swap(alice, blank);
  cout << "alice" << endl;
  sdebug(alice);
  sdebug(blank);

  ft::set<char> bob;
  rep(i, 4) bob.insert('Z' - i);

  cout << "alice" << endl;
  sdebug(alice);
  cout << "bob" << endl;
  sdebug(bob);
  std::swap(alice, bob);
  cout << "alice" << endl;
  sdebug(alice);
  cout << "bob" << endl;
  sdebug(bob);
  cout << "std::swap(alice, bob)" << endl;
  std::swap(alice, bob);
  cout << "alice" << endl;
  sdebug(alice);
  cout << "bob" << endl;
  sdebug(bob);
  cout << "alice.swap(bob)" << endl;
  alice.swap(bob);
  cout << "alice" << endl;
  sdebug(alice);
  cout << "bob" << endl;
  sdebug(bob);
  cout << "bob.swap(alice)" << endl;
  bob.swap(alice);
  cout << "alice" << endl;
  sdebug(alice);
  cout << "bob" << endl;
  sdebug(bob);
}

template <class Con>
void set_find_test_out(Con& S) {
  rep(i, 5) {
    typename Con::iterator it = S.find(i);
    if (it != S.end())
      cout << "S:" << *it << " count:" << S.count(i) << endl;
    else
      cout << "S:"
           << "end()"
           << " count:" << S.count(i) << endl;
  }
}

template <class Con>
void set_find_test_const_out(const Con& S) {
  rep(i, 5) {
    typename Con::const_iterator it = S.find(i);
    if (it != S.end())
      cout << "S[" << i << "]:" << *it << " count:" << S.count(i) << endl;
    else
      cout << "S[" << i << "]:"
           << "end()"
           << " count:" << S.count(i) << endl;
  }
}

void set_find_test() {
  pout("set_find_test");

  ft::set<int> S;

  rep(i, 3) S.insert(i);
  set_find_test_out(S);
  set_find_test_const_out(S);
}

template <class Con>
void set_equal_range_test_out(Con& s) {
    typename std::pair<typename Con::iterator,
                       typename Con::iterator>
        p = s.equal_range("one");
    for (typename Con::iterator& q = p.first; q != p.second; ++q) {
      cout << "s[" << *q << "] " << '\n';
    }

    if (p.second == s.find("two")) {
      cout << "end of equal_range (p.second) is one-past p.first\n";
    } else {
      cout << "unexpected; p.second expected to be one-past p.first\n";
    }
}

template <class Con>
void set_equal_range_test_const_out(const Con& s) {
  {
    typename std::pair<typename Con::const_iterator,
                       typename Con::const_iterator>
        p = s.equal_range("one");
    for (typename Con::const_iterator& q = p.first; q != p.second; ++q) {
      cout << "s[" << *q << "] " << '\n';
    }

    if (p.second == s.find("two")) {
      cout << "end of equal_range (p.second) is one-past p.first\n";
    } else {
      cout << "unexpected; p.second expected to be one-past p.first\n";
    }
  }

  {
    typename std::pair<typename Con::const_iterator,
                       typename Con::const_iterator>
        pp = s.equal_range("a");
    if (pp.first == s.begin()) {
      cout << "pp.first is iterator to first not-less than -1\n";
    } else {
      cout << "unexpected pp.first\n";
    }

    if (pp.second == s.begin()) {
      cout << "pp.second is iterator to first element greater-than -1\n";
    } else {
      cout << "unexpected pp.second\n";
    }
  }

  {
    typename std::pair<typename Con::const_iterator,
                       typename Con::const_iterator>
        ppp = s.equal_range("three");
    if (ppp.first == s.end()) {
      cout << "ppp.first is iterator to first not-less than 3\n";
    } else {
      cout << "unexpected ppp.first\n";
    }

    if (ppp.second == s.end()) {
      cout << "ppp.second is iterator to first element greater-than 3\n";
    } else {
      cout << "unexpected ppp.second\n";
    }
  }
}

void set_equal_range_test() {
  pout("set_equal_range_test");

  ft::set<const char*> s;
  s.insert("zero");
  s.insert("one");
  s.insert("two");

  set_equal_range_test_out(s);
  set_equal_range_test_const_out(s);
}

void set_copy_construct_test() {
  pout("set_copy_construct_test");

  ft::set<const char*> s;
  s.insert("zero");
  s.insert("one");
  s.insert("two");

  const ft::set<const char*> cs = s;
  ft::set<const char*> ss = s;
  sdebug(s);
  sdebug(cs);
  sdebug(ss);
}

void set_lower_bound_test() {
  ft::set<int> S;
  int N = 5;
  int NN = 10;
  rep(i, N) S.insert(i + 3);

  rep(i, NN) {
    ft::set<int>::iterator it = S.lower_bound(i);
    cout << "S.lower_bound(" << i << "):";
    if (it == S.end())
      cout << "end()" << endl;
    else
      cout << *it << endl;
  }
  rep(i, NN) {
    ft::set<int>::iterator it = S.upper_bound(i);
    cout << "S.upper_bound(" << i << "):";
    if (it == S.end())
      cout << "end()" << endl;
    else
      cout << *it << endl;
  }

  const ft::set<int> CS = S;

  rep(i, NN) {
    ft::set<int>::const_iterator it = CS.lower_bound(i);
    cout << "CS.lower_bound(" << i << "):";
    if (it == CS.end())
      cout << "end()" << endl;
    else
      cout << *it << endl;
  }
  rep(i, NN) {
    ft::set<int>::const_iterator it = CS.upper_bound(i);
    cout << "CS.upper_bound(" << i << "):";
    if (it == CS.end())
      cout << "end()" << endl;
    else
      cout << *it << endl;
  }
}

struct ModCmp_comp_test {
  bool operator()(const int lhs, const int rhs) const {
    return (lhs % 97) < (rhs % 97);
  }
};

void set_key_comp_test() {
  pout("set_key_comp_test");

  ft::set<int, ModCmp_comp_test> cont;
  int N = 5;
  rep(i, N) cont.insert(i + 1);

  ModCmp_comp_test comp_func = cont.key_comp();

  for (ft::set<int, ModCmp_comp_test>::iterator it = cont.begin();
       it != cont.end(); ++it) {
    int key = *it;
    bool before = comp_func(key, 100);
    bool after = comp_func(100, key);
    if (!before && !after)
      cout << key << " equivalent to key 100\n";
    else if (before)
      cout << key << " goes before key 100\n";
    else if (after)
      cout << key << " goes after key 100\n";
  }
}

void set_value_comp_test() {
  pout("set_value_comp_test");

  ft::set<int, ModCmp_comp_test> cont;
  int N = 5;
  rep(i, N) cont.insert(i + 1);

  ModCmp_comp_test comp_func = cont.value_comp();

  for (ft::set<int, ModCmp_comp_test>::iterator it = cont.begin();
       it != cont.end(); ++it) {
    int key = *it;
    bool before = comp_func(key, 100);
    bool after = comp_func(100, key);
    if (!before && !after)
      cout << key << " equivalent to key 100\n";
    else if (before)
      cout << key << " goes before key 100\n";
    else if (after)
      cout << key << " goes after key 100\n";
  }
}

void set_non_member_operator_test() {
  ft::set<char> alice;
  rep(i, 3) alice.insert('a' + i);
  ft::set<char> bob;
  rep(i, 4) bob.insert('Z' - i);
  ft::set<char> eve;
  rep(i, 3) eve.insert('a' + i);

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

struct Point_constructs_test {
  double x, y;
};
struct PointCmp_constructs_test {
  bool operator()(const Point_constructs_test& lhs,
                  const Point_constructs_test& rhs) const {
    return lhs.x < rhs.x;  // NB. intentionally ignores y
  }
};

void set_constructs_test() {
  pout("set_constructs_test");
  // (1) Default constructor
  ft::set<std::string> a;
  a.insert("cat");
  a.insert("dog");
  a.insert("horse");
  sdebug(a);

  // (2) Iterator constructor
  ft::set<std::string> b(a.find("cat"), a.end());
  sdebug(b);
  ft::set<std::string> b2(a.find("dog"), a.end());
  sdebug(b2);

  // (3) Copy constructor
  ft::set<std::string> c(a);
  c.insert("another horse");
  sdebug(c);

  // custom comparison
  ft::set<Point_constructs_test, PointCmp_constructs_test> z;
  z.insert({2, 5});
  z.insert({3, 4});
  z.insert({1, 1});
  z.insert({1, -1});  // this fails because the magnitude of 1,-1 equals 1,1
  for (ft::set<Point_constructs_test, PointCmp_constructs_test>::iterator it = z.begin();
       it != z.end(); ++it){
         Point_constructs_test p = *it;
         cout << '(' << p.x << ',' << p.y << ") ";
       }
  cout << '\n';
}

void set_test() {
  //	set_insert_delete_hardtest();
  set_insert_test();
//  map_value_compare_test();
  set_operator_equal_test();
  set_all_erase_test();
  set_get_alloc_test();
//  set_at_test();
  set_insert_iterator_test();
  set_insert_iterator_iterator_test();
  //  set_operator_kakko_test();
  set_begin_test();
  set_rbegin_test();
  set_empty_test();
  set_max_size_test();
  set_clear_test();
  set_erase_test();
  set_swap_test();
  set_find_test();
  set_equal_range_test();
  set_copy_construct_test();
  set_lower_bound_test();
  set_key_comp_test();
  set_value_comp_test();
  set_non_member_operator_test();
  set_constructs_test();
}