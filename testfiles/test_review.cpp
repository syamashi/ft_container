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

template <typename T, typename U>
void mdebug(ft::map<T, U> const& M) {
  cout << "size:" << M.size() << endl;

  for (typename ft::map<T, U>::const_iterator it = M.begin(); it != M.end();
       ++it) {
    cout << "M[" << it->first << "]:" << it->second << endl;
  }
  cout << endl;
}

void out_time(std::string name, double time) {
  cerr << name << ":" << time << endl;
}

void review_vector_dynamic_array() {
  pout("review_vector_dynamic_array");

  int N = 10;
  ft::vector<int> V;
  vdebug(V);
  for (int i = 0; i < N; ++i) {
    V.push_back(i);
    vdebug(V);
  }
}

void review_vector_comp_cit_it() {
  pout("review_vector_comp_cit_it");

  int N = 10;
  ft::vector<int> V;
  for (int i = 0; i < N; ++i) V.push_back(i);

  for (ft::vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
    ft::vector<int>::const_iterator cit = it;
    if (cit == it) cout << *cit << " ";
    if (it != cit)
      cout << "error" << endl;
    else
      cout << *it << endl;
  }
}

void review_vector_swap() {
  pout("review_vector_swap");

  int N = 10;
  ft::vector<int> V, V2;
  for (int i = 0; i < N; ++i) V.push_back(i);
  for (int i = 0; i < N * 2; ++i) V2.push_back(i + N);

  cout << "<before swap>" << endl;
  vdebug(V);
  vdebug(V2);
  cout << "<after swap>" << endl << endl;
  V.swap(V2);
  vdebug(V);
  vdebug(V2);
  cout << "<after std::swap(V, V2)>" << endl << endl;
  std::swap(V, V2);
  vdebug(V);
  vdebug(V2);
}

void review_vector_refer_elements() {
  pout("review_vector_refer_elements");

  int N = 10;
  ft::vector<int> V;
  for (int i = 0; i < N; ++i) V.push_back(i);

  // referred to before the call
  ft::vector<int>::iterator it = V.begin();
  ft::vector<int>::pointer p = V.data();   // V.begin()
  ft::vector<int>::reference r = V.at(0);  // V[0]

  cout << "<before>" << endl;
  cout << *it << " " << *p << " " << r << endl;

  // they now iterate.
  V[0] = 42;
  cout << "<after>" << endl;
  cout << *it << " " << *p << " " << r << endl;

  ft::vector<int>::iterator ait = V.begin();
  *ait = 43;
  cout << "<after>" << endl;
  cout << *it << " " << *p << " " << r << endl;
}

void review_vector_time() {
  std::chrono::system_clock::time_point clockstart, clockend;
  clockstart = std::chrono::system_clock::now();

  ft::vector<int> V;
  V.assign(1000000, 42);

  clockend = std::chrono::system_clock::now();
  double time = std::chrono::duration_cast<std::chrono::microseconds>(
                    clockend - clockstart)
                    .count();
  out_time("vector", time);
}

void review_map_make_pair() {
  pout("review_map_make_pair");
  ft::map<int, char> M;
  M.insert(ft::make_pair(100, 'a'));
  M.insert(ft::make_pair(0, 'b'));
  M.insert(ft::make_pair(30, 'c'));
  M.insert(ft::make_pair(-42, 'd'));

  mdebug(M);
  // never two of the same Key
  cout << "<insert twice>" << endl;
  M.insert(ft::make_pair(100, 'z'));
  M.insert(ft::make_pair(0, 'y'));
  M.insert(ft::make_pair(30, 'x'));
  M.insert(ft::make_pair(-42, 'w'));
  mdebug(M);
}

void review_map_insert_delete() {
  pout("review_map_insert_delete");
  ft::map<int, int> M;
  int N = 10;

  for (int i = 0; i < N; ++i) M.insert({i, i});
  mdebug(M);
  for (int i = 0; i < N + 3; ++i) {
    int j = (i + 5) % N;
    M.erase(j);
    cout << "<erase>:" << j << endl;
    mdebug(M);
  }
}

void review_map_swap() {
  pout("review_map_swap");

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

void review_map_time() {
  std::chrono::system_clock::time_point clockstart, clockend;
  clockstart = std::chrono::system_clock::now();

  ft::map<int, int> M;
  int N = 100000;

  for (int i = 0; i < N; ++i) M[i] = i;
  for (int i = 0; i < N; ++i) M.erase(i);

  clockend = std::chrono::system_clock::now();
  double time = std::chrono::duration_cast<std::chrono::microseconds>(
                    clockend - clockstart)
                    .count();
  out_time("map", time);
}

void review_vector_test() {
  review_vector_dynamic_array();
  review_vector_comp_cit_it();
  review_vector_swap();
  review_vector_refer_elements();
  review_vector_time();
}

void review_map_test() {
  review_map_make_pair();
  review_map_insert_delete();
  review_map_swap();
  review_map_time();
}

void review_stack_test() {
  pout("review_stack_test");

  ft::stack<int, ft::vector<int>> SV;
  SV.push(1);
  ft::stack<int, std::deque<int>> SD;
  SD.push(2);
  ft::stack<int, std::list<int>> SL;
  SL.push(3);

  cout << SV.top() << SD.top() << SL.top() << endl;
  SV.pop();
  SD.pop();
  SL.pop();
}
void review_test() {
  review_vector_test();
  review_map_test();
  review_stack_test();
}
