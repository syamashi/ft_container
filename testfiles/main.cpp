#include "tester.hpp"

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
