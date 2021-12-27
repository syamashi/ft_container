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
  clock_t clockstart, clockend;
  clockstart = clock();
  vector_test();
  stack_test();
  map_test();
  set_test();
  review_test();
  clockend = clock();
  double time = (double)(clockend - clockstart);
  cerr << "totaltime:" << time << endl;
}
