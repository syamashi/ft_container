#include "tester.hpp"

void bitout(size_t n){
  rep(i, 64){
    cout << ((n>>(63-i))&1);
    if (i%8==7) cout << " ";
  }
  cout << endl;
}

double dist(double x1, double y1) {
  return (std::sqrt(x1 * x1 + y1 * y1));
}

int main() {
//  vector_test();
//  stack_test();
  map_test();
}
