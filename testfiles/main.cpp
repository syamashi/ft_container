#include "tester.hpp"
double dist(double x1, double y1) {
  return (std::sqrt(x1 * x1 + y1 * y1));
}

void bitout(size_t n){
  rep(i, 64){
    cerr << ((n>>(63-i))&1);
    if (i%8==7) cerr << " ";
  }
  cerr << endl;
}


int main() {
  clock_t clockstart, clockend;
  clockstart = clock();
	vector_test();
	stack_test();
	map_test();
	set_test();
  util_test();
  review_test();
  clockend = clock();
  double time = (double)(clockend - clockstart);
  cerr << "totaltime:" << time << endl;
}
