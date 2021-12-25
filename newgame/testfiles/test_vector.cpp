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

void vector_test() {
  vector_construct_test();
  vector_copy_construct_test();
}
