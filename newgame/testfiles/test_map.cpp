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

  for (typename ft::map<T, U>::const_iterator it = M.begin(); it != M.end();
       ++it) {
    cout << "M[" << it->first << "]:" << it->second << endl;
  }
  cout << endl;
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
    ft::pair<ft::map<int, int>::iterator, bool> ret =
        M.insert(ft::make_pair(key, val));
    cout << " size:" << M.size() << endl;
    cout << " ret:" << ret.first->first << "," << ret.first->second << " "
         << ret.second << endl;
    cout << endl;
  }
}

void map_test() {
  map_insert_test();
}