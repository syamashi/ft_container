#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>

#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <typename T, typename U>
void mdebug(ft::map<T, U> const& M) {
  cout << "size:" << M.size() << endl;

  for (auto it = M.begin(); it != M.end(); ++it) {
    cout << "M[" << it->first << "]:" << it->second << endl;
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

void map_insert_test() {
  pout("map_insert_test");

  ft::map<int, int> M;
  rep(i, 20) {
    int key = 0 - i;
    int val = 0 - i;
    cout << "--- "
         << "M.insert({" << key << "," << val << "})"
         << " ---" << endl;
    std::pair<ft::map<int, int>::iterator, bool> ret = M.insert({key, val});
    cout << " size:" << M.size() << endl;
    cout << " ret:" << ret.first->first << "," << ret.first->second << " "
         << ret.second << endl;
    cout << endl;
  }
}

/*
void map_insert_delete_hardtest(){
        // 開始地点を20か所ずらして、連番で作成
        ft::map<int, int> M;
  int N=20;
  rep(i, N){ // start
    rep(j, N){
      int k=(i+j)%N;
                M.insert({k, k});
                M.debug2();
    }
        rep(j, N+10){
      int k=(i+j)%N;
      M.erase(k);
      M.debug2();
        }
  }
}
*/

void map_value_compare_test() {
  pout("map_value_compare_test");
  ft::map<int, char> c;
  const ft::map<int, char>::value_compare& comp = c.value_comp();

  std::pair<int, char> p1 = std::make_pair(1, 'a');
  std::pair<int, char> p2 = std::make_pair(2, 'b');
  std::pair<int, char> p3 = std::make_pair(3, 'c');

  cout << comp(p1, p2) << endl;
  cout << comp(p3, p2) << endl;
}

void map_operator_equal_test() {
  pout("map_operator_equal_test");

  ft::map<int, int> nums1;

  rep(i, 10) { nums1.insert({i, i}); }
  ft::map<int, int> nums2;

  cout << "Initially:\n";
  cout << "---nums1---" << endl;
  mdebug(nums1);
  cout << "---nums2---" << endl;
  mdebug(nums2);

  // copy assignment copies data from nums1 to nums2
  nums2 = nums1;

  cout << "After assigment:\n";
  cout << "---nums1---" << endl;
  mdebug(nums1);
  cout << "---nums2---" << endl;
  mdebug(nums2);
}

void map_all_erase_test() {
  pout("map_all_erase_test");
  ft::map<int, int> M;
  int N = 5;
  rep(i, N) {  // start
    rep(j, N) {
      int k = (i + j) % N;
      M.insert({k, k});
    }
    cout << "ins:" << i << endl;
    mdebug(M);
    rep(j, N + 10) {
      int k = (i + j) % N;
      M.erase(k);
    }
    cout << "ers:" << i << endl;
    mdebug(M);
  }
}

void map_get_alloc_test() {
  pout("map_get_alloc_test");

  ft::map<int, int> M;
  ft::map<int, int>::allocator_type al = M.get_allocator();
  std::pair<const int, int>* p = al.allocate(1);
  std::pair<const int, int> q = {1, 2};
  al.construct(p, q);
  cout << p->first << endl;
  al.deallocate(p, 1);
}

template <class Container, class T>
void at_wrap_at_test(Container& c, T v) {
  try {
    cout << c.at(v) << endl;
  } catch (std::out_of_range&) {
    cout << "exception std::out_of_range" << endl;
  }
}

template <class Container, class T>
void const_at_wrap_at_test(const Container& c, T v) {
  try {
    cout << c.at(v) << endl;
  } catch (std::out_of_range&) {
    cout << "exception std::out_of_range" << endl;
  }
}

void map_at_test() {
  pout("map_at_test");
  ft::map<int, char> m;
  m.insert(std::make_pair(1, 'a'));

  at_wrap_at_test(m, 1);
  at_wrap_at_test(m, 2);
  const_at_wrap_at_test(m, 1);
  const_at_wrap_at_test(m, 2);
}

void map_insert_iterator_test() {
  pout("map_insert_iterator_test");

  ft::map<int, int> M;
  rep(i, 10) M[i * 2] = i * 2;
  ft::map<int, int>::iterator ret;

  cout << "---M.insert(M.end(), {4,2})---" << endl;
  ret = M.insert(M.end(), {4, 2});
  cout << "ret[" << ret->first << "]:" << ret->second << endl;
  mdebug(M);
  cout << "---M.insert(M.begin(), {4,2})---" << endl;
  ret = M.insert(M.begin(), {4, 2});
  cout << "ret[" << ret->first << "]:" << ret->second << endl;
  mdebug(M);
  cout << "---M.insert(M.end(), {5,2})---" << endl;
  ret = M.insert(M.end(), {5, 2});
  cout << "ret[" << ret->first << "]:" << ret->second << endl;
  mdebug(M);
  cout << "---M.insert(M.begin(), {7,2})---" << endl;
  ret = M.insert(M.begin(), {7, 2});
  cout << "ret[" << ret->first << "]:" << ret->second << endl;
  mdebug(M);
}

void map_insert_iterator_iterator_test() {
  pout("map_insert_iterator_iterator_test");
  ft::map<int, int> M;
  ft::map<int, int> MM;
  rep(i, 10) M[i * 2] = i * 2;
  rep(i, 10) MM[i * 2 + 1] = i * 2 + 1;

  M.insert(MM.begin(), MM.end());
  mdebug(M);
  M.insert(MM.begin(), MM.end());
  mdebug(M);
}

void map_operator_kakko_test() {
  pout("map_operator_kakko_test");

  ft::map<int, int> M;
  rep(i, 3) M[i];
  rep(i, 3) M[i + 3] = i + 3;
  mdebug(M);

  rep(i, 10) M[i] = i + 100;
  mdebug(M);
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
  for (ft::map<Point_begin_test*, double, PointCmp_begin_test>::iterator iter =
           mag.begin();
       iter != mag.end(); ++iter) {
    Point_begin_test* cur = iter->first;
    mag[cur] = std::hypot(cur->x, cur->y);  // hypot == sqrt(a,b)
    cout << "The magnitude of (" << cur->x << ", " << cur->y << ") is ";
    cout << iter->second << '\n';
  }

  // Repeat the above with the range-based for loop
  for (ft::map<Point_begin_test*, double, PointCmp_begin_test>::iterator iter =
           mag.begin();
       iter != mag.end(); ++iter) {
    Point_begin_test* cur = iter->first;
    cur->y = iter->second;
    mag[cur] = std::hypot(cur->x, cur->y);
    cout << "The magnitude of (" << cur->x << ", " << cur->y << ") is ";
    cout << mag[cur] << '\n';
  }
}

template <class Con>
void begin_test_const_out(const Con& mag) {
  // Update and print the magnitude of each node
  for (ft::map<Point_begin_test*, double, PointCmp_begin_test>::const_iterator
           iter = mag.begin();
       iter != mag.end(); ++iter) {
    Point_begin_test* cur = iter->first;
    //    mag[cur] = std::hypot(cur->x, cur->y); // hypot == sqrt(a,b)
    cout << "The magnitude of (" << cur->x << ", " << cur->y << ") is ";
    cout << iter->second << '\n';
  }

  // Repeat the above with the range-based for loop
  for (ft::map<Point_begin_test*, double, PointCmp_begin_test>::const_iterator
           iter = mag.begin();
       iter != mag.end(); ++iter) {
    Point_begin_test* cur = iter->first;
    cur->y = iter->second;
    //    mag[cur] = std::hypot(cur->x, cur->y);
    cout << "The magnitude of (" << cur->x << ", " << cur->y << ") is ";
    cout << "const" << '\n';
  }
}

void map_begin_test() {
  Point_begin_test points[3];
  points[0] = {2, 0};
  points[1] = {1, 0};
  points[2] = {3, 0};

  // points[].first でsortされる
  ft::map<Point_begin_test*, double, PointCmp_begin_test> mag;
  mag[points] = 2;
  mag[points + 1] = 1;
  mag[points + 2] = 3;

  for (ft::map<Point_begin_test*, double, PointCmp_begin_test>::iterator iter =
           mag.begin();
       iter != mag.end(); ++iter) {
    Point_begin_test* cur = iter->first;  // pointer to Node
    cur->y = mag[cur];  // could also have used  cur->y = iter->second;
  }
  begin_test_out(mag);
  begin_test_const_out(mag);
}

template <class Con>
void map_rbegin_test_out(Con& coins) {
  cout << "US coins in circulation, largest to smallest denomination:\n";
  for (ft::map<int, std::string>::reverse_iterator it = coins.rbegin();
       it != coins.rend(); ++it) {
    cout << std::setw(11) << it->second << " = ¢" << it->first << '\n';
  }
}

template <class Con>
void map_rbegin_test_const_out(const Con& coins) {
  cout << "US coins in circulation, largest to smallest denomination:\n";
  for (ft::map<int, std::string>::const_reverse_iterator it = coins.rbegin();
       it != coins.rend(); ++it) {
    cout << std::setw(11) << it->second << " = ¢" << it->first << '\n';
  }
}

void map_rbegin_test() {
  pout("map_rbegin_test");

  ft::map<int, std::string> coins;
  coins[10] = "dime";
  coins[100] = "dollar";
  coins[50] = "half_dollar";
  coins[5] = "nickel";
  coins[1] = "penny";
  coins[25] = "quarter";

  map_rbegin_test_out(coins);
  map_rbegin_test_const_out(coins);
}

void map_empty_test() {
  pout("map_empty_test");

  ft::map<int, int> M;

  int N = 5;
  rep(i, N) {
    rep(j, i) M[j] = j;
    cout << "ins:" << M.empty() << " size:" << M.size() << endl;
    rep(j, i) M.erase(j);
    cout << "ers:" << M.empty() << " size:" << M.size() << endl;
  }
}

void map_max_size_test() {
  pout("map_max_size_test");

  ft::map<int, int> MII;
  ft::map<char, char> MCC;

  cout << "int:" << MII.max_size() << endl;
  cout << "char:" << MCC.max_size() << endl;
}

void map_clear_test() {
  pout("map_clear_test");

  ft::map<int, int> M;

  int N = 5;
  rep(i, N) {
    rep(j, i) M[j - 100] = j - 100;
    cout << "ins:" << i << endl;
    mdebug(M);
    cout << "clear" << endl;
    M.clear();
    mdebug(M);
  }
}

void map_erase_test() {
  pout("map_erase_test");

  ft::map<int, int> M;
  int N = 5;

  rep(i, N) M[i] = i;
  rep(i, N * 2) {
    size_t ret = M.erase((i + 1) % N);
    cout << "erase_key:" << i << " ret:" << ret << endl;
  }

  rep(i, N) M[i] = i;
  for (ft::map<int, int>::iterator it = M.begin(); it != M.end();) {
    cout << "M.erase(" << it->first << ")" << endl;
    M.erase(it++);
    mdebug(M);
  }

  rep(i, N) {  // 開始位置
    rep(j, N) M[j] = j;
    ft::map<int, int>::iterator it = M.begin();
    rep(j, i)++ it;
    cout << "M.erase(" << M.begin()->first << "," << it->first << ")" << endl;
    M.erase(M.begin(), it);
    mdebug(M);
    M.clear();
  }

  rep(i, N) {  // 開始位置
    rep(j, N) M[j] = j;
    ft::map<int, int>::iterator it = M.end();
    rep(j, i + 1)-- it;
    cout << "M.erase(" << it->first << ",M.end())" << endl;
    M.erase(it, M.end());
    mdebug(M);
    M.clear();
  }
}

void map_swap_test() {
  pout("map_swap_test");

  ft::map<int, char> alice;
  alice[1] = 'a';
  alice[2] = 'b';
  alice[3] = 'c';

  ft::map<int, char> blank;
  cout << "alice.swap(blank)" << endl;
  alice.swap(blank);
  cout << "alice" << endl;
  mdebug(alice);
  mdebug(blank);
  cout << "alice.swap(blank)" << endl;
  alice.swap(blank);
  cout << "alice" << endl;
  mdebug(alice);
  mdebug(blank);

  cout << "blank.swap(alice)" << endl;
  blank.swap(blank);
  cout << "alice" << endl;
  mdebug(alice);
  mdebug(blank);
  cout << "blank.swap(alice)" << endl;
  blank.swap(blank);
  cout << "alice" << endl;
  mdebug(alice);
  mdebug(blank);

  cout << "std::swap(alice, blank)" << endl;
  std::swap(alice, blank);
  cout << "alice" << endl;
  mdebug(alice);
  mdebug(blank);
  cout << "std::swap(alice, blank)" << endl;
  std::swap(alice, blank);
  cout << "alice" << endl;
  mdebug(alice);
  mdebug(blank);

  ft::map<int, char> bob;
  bob[7] = 'Z';
  bob[8] = 'Y';
  bob[9] = 'X';
  bob[10] = 'W';

  cout << "alice" << endl;
  mdebug(alice);
  cout << "bob" << endl;
  mdebug(bob);
  std::swap(alice, bob);
  cout << "alice" << endl;
  mdebug(alice);
  cout << "bob" << endl;
  mdebug(bob);
  cout << "std::swap(alice, bob)" << endl;
  std::swap(alice, bob);
  cout << "alice" << endl;
  mdebug(alice);
  cout << "bob" << endl;
  mdebug(bob);
  cout << "alice.swap(bob)" << endl;
  alice.swap(bob);
  cout << "alice" << endl;
  mdebug(alice);
  cout << "bob" << endl;
  mdebug(bob);
  cout << "bob.swap(alice)" << endl;
  bob.swap(alice);
  cout << "alice" << endl;
  mdebug(alice);
  cout << "bob" << endl;
  mdebug(bob);
}

template <class Con>
void map_find_test_out(Con& M) {
  rep(i, 5) {
    typename Con::iterator it = M.find(i);
    if (it != M.end())
      cout << "M[" << i << "]:" << it->first << " count:" << M.count(i) << endl;
    else
      cout << "M[" << i << "]:"
           << "end()"
           << " count:" << M.count(i) << endl;
  }
}

template <class Con>
void map_find_test_const_out(const Con& M) {
  rep(i, 5) {
    typename Con::const_iterator it = M.find(i);
    if (it != M.end())
      cout << "M[" << i << "]:" << it->first << " count:" << M.count(i) << endl;
    else
      cout << "M[" << i << "]:"
           << "end()"
           << " count:" << M.count(i) << endl;
  }
}

void map_find_test() {
  pout("map_find_test");

  ft::map<int, int> M;

  rep(i, 3) M[i] = i;
  map_find_test_out(M);
  map_find_test_const_out(M);
}

template <class Con>
void map_equal_range_test_out(Con& m) {}

template <class Con>
void map_equal_range_test_const_out(const Con& m) {
  {
    typename std::pair<typename Con::const_iterator,
                       typename Con::const_iterator>
        p = m.equal_range(1);
    for (typename Con::const_iterator& q = p.first; q != p.second; ++q) {
      cout << "m[" << q->first << "] = " << q->second << '\n';
    }

    if (p.second == m.find(2)) {
      cout << "end of equal_range (p.second) is one-past p.first\n";
    } else {
      cout << "unexpected; p.second expected to be one-past p.first\n";
    }
  }

  {
    typename std::pair<typename Con::const_iterator,
                       typename Con::const_iterator>
        pp = m.equal_range(-1);
    if (pp.first == m.begin()) {
      cout << "pp.first is iterator to first not-less than -1\n";
    } else {
      cout << "unexpected pp.first\n";
    }

    if (pp.second == m.begin()) {
      cout << "pp.second is iterator to first element greater-than -1\n";
    } else {
      cout << "unexpected pp.second\n";
    }
  }

  {
    typename std::pair<typename Con::const_iterator,
                       typename Con::const_iterator>
        ppp = m.equal_range(3);
    if (ppp.first == m.end()) {
      cout << "ppp.first is iterator to first not-less than 3\n";
    } else {
      cout << "unexpected ppp.first\n";
    }

    if (ppp.second == m.end()) {
      cout << "ppp.second is iterator to first element greater-than 3\n";
    } else {
      cout << "unexpected ppp.second\n";
    }
  }
}

void map_equal_range_test() {
  pout("map_equal_range_test");

  ft::map<int, const char*> m;
  m[0] = "zero";
  m[1] = "one";
  m[2] = "two";

  map_equal_range_test_out(m);
  map_equal_range_test_const_out(m);
}

void map_copy_construct_test() {
  pout("map_copy_construct_test");

  ft::map<int, const char*> m;
  m[0] = "zero";
  m[1] = "one";
  m[2] = "two";

  const ft::map<int, const char*> cm = m;
  ft::map<int, const char*> mm = m;
  mdebug(m);
  mdebug(cm);
  mdebug(mm);
}

void map_lower_bound_test() {
  ft::map<int, int> M;
  int N = 5;
  int NN = 10;
  rep(i, N) M[i + 3] = i + 3;

  rep(i, NN) {
    ft::map<int, int>::iterator it = M.lower_bound(i);
    cout << "M.lower_bound(" << i << "):";
    if (it == M.end())
      cout << "end()" << endl;
    else
      cout << it->first << endl;
  }
  rep(i, NN) {
    ft::map<int, int>::iterator it = M.upper_bound(i);
    cout << "M.upper_bound(" << i << "):";
    if (it == M.end())
      cout << "end()" << endl;
    else
      cout << it->first << endl;
  }

  const ft::map<int, int> CM = M;

  rep(i, NN) {
    ft::map<int, int>::const_iterator it = CM.lower_bound(i);
    cout << "CM.lower_bound(" << i << "):";
    if (it == CM.end())
      cout << "end()" << endl;
    else
      cout << it->first << endl;
  }
  rep(i, NN) {
    ft::map<int, int>::const_iterator it = CM.upper_bound(i);
    cout << "CM.upper_bound(" << i << "):";
    if (it == CM.end())
      cout << "end()" << endl;
    else
      cout << it->first << endl;
  }
}

struct ModCmp_comp_test {
  bool operator()(const int lhs, const int rhs) const {
    return (lhs % 97) < (rhs % 97);
  }
};

void map_key_comp_test() {
  pout("map_key_comp_test");

  ft::map<int, int, ModCmp_comp_test> cont;
  int N = 5;
  rep(i, N) cont[i + 1] = i + 1;

  ModCmp_comp_test comp_func = cont.key_comp();

  for (ft::map<int, int, ModCmp_comp_test>::iterator it = cont.begin();
       it != cont.end(); ++it) {
    int key = it->first;
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

void map_value_comp_test() {
  pout("map_value_comp_test");

  ft::map<int, int, ModCmp_comp_test> cont;
  int N = 5;
  rep(i, N) cont[i + 1] = i + 1;

  ft::map<int, int, ModCmp_comp_test>::value_compare comp_func = cont.value_comp();

  for (ft::map<int, int, ModCmp_comp_test>::iterator it = cont.begin();
       it != cont.end(); ++it) {
    const std::pair<int, int> key = *it;
    bool before = comp_func(key, {100,100});
    bool after = comp_func({100,100}, key);
    if (!before && !after)
      cout << key.first << " equivalent to key 100\n";
    else if (before)
      cout << key.first << " goes before key 100\n";
    else if (after)
      cout << key.first << " goes after key 100\n";
  }
}

void map_non_member_operator_test() {
  ft::map<int, char> alice;
  alice[1] = 'a';
  alice[2] = 'b';
  alice[3] = 'c';
  ft::map<int, char> bob;
  bob[7] = 'Z';
  bob[8] = 'Y';
  bob[9] = 'X';
  bob[10] = 'W';
  ft::map<int, char> eve;
  eve[1] = 'a';
  eve[2] = 'b';
  eve[3] = 'c';

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

void map_constructs_test() {
  pout("map_constructs_test");
  // (1) Default constructor
  ft::map<std::string, int> map1;
  map1["something"] = 69;
  map1["anything"] = 199;
  map1["that thing"] = 50;
  cout << "map1 = ";
  mdebug(map1);

  // (2) Range constructor
  ft::map<std::string, int> iter(map1.find("anything"), map1.end());
  cout << "\niter = ";
  mdebug(iter);
  cout << "map1 = ";
  mdebug(map1);

  ft::map<std::string, int> iter2(map1.find("something"), map1.end());
  cout << "\niter2 = ";
  mdebug(iter2);
  cout << "map1 = ";
  mdebug(map1);

  // (3) Copy constructor
  ft::map<std::string, int> copied(map1);
  cout << "\ncopied = ";
  mdebug(copied);
  cout << "map1 = ";
  mdebug(map1);

  // Custom Key class option 1:
  // Use a comparison struct
  ft::map<Point_constructs_test, double, PointCmp_constructs_test> mag;
  mag[{5, -12}] = 13;
  mag[{3, 4}] = 5;
  mag[{-8, -15}] = 17;
  for (std::pair<const Point_constructs_test, double> p : mag)
    cout << "The magnitude of (" << p.first.x << ", " << p.first.y << ") is "
         << p.second << '\n';
}

void map_test() {
  //	map_insert_delete_hardtest();
  map_insert_test();
  map_value_compare_test();
  map_operator_equal_test();
  map_all_erase_test();
  map_get_alloc_test();
  map_at_test();
  map_insert_iterator_test();
  map_insert_iterator_iterator_test();
  map_operator_kakko_test();
  map_begin_test();
  map_rbegin_test();
  map_empty_test();
  map_max_size_test();
  map_clear_test();
  map_erase_test();
  map_swap_test();
  map_find_test();
  map_equal_range_test();
  map_copy_construct_test();
  map_lower_bound_test();
  map_key_comp_test();
  map_value_comp_test();
  map_non_member_operator_test();
  map_constructs_test();
}