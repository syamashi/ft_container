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
    if (it == cit) cout << *it << endl;
  }
}


void review_vector_swap() {
  pout("review_vector_swap");

  int N = 10;
  ft::vector<int> V, V2;
  for (int i = 0; i < N; ++i) V.push_back(i);
  for (int i = 0; i < N*2; ++i) V2.push_back(i + N);

  cout << "<before swap>" << endl;
  vdebug(V);
  vdebug(V2);
  cout << "<after swap>" << endl;
  V.swap(V2);
  vdebug(V);
  vdebug(V2);
  cout << "<after std::swap(V, V2)>" << endl;
  std::swap(V, V2);
  vdebug(V);
  vdebug(V2);
}
void review_vector_test() {
  review_vector_dynamic_array();
  review_vector_comp_cit_it();
  review_vector_swap();
}

void review_stack_test(){

}

void review_test() {
  review_vector_test();
  review_stack_test();
  }
