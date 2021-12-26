#include "tester.hpp"

void bitout(size_t n){
  rep(i, 64){
    cout << ((n>>(63-i))&1);
    if (i%8==7) cout << " ";
  }
  cout << endl;
}

int main() {
//  vector_test();
//  stack_test();
  map_test();
}
