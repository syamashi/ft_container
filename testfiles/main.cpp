#include "tester.hpp"

int main() {
  std::chrono::system_clock::time_point  clockstart, clockend;
  clockstart = std::chrono::system_clock::now();
	vector_test();
	stack_test();
	map_test();
	set_test();
  util_test();
  review_test();
  clockend = std::chrono::system_clock::now();
  double time = std::chrono::duration_cast<std::chrono::microseconds>(clockend - clockstart).count();
  cerr << "totaltime:" << time << endl;
}
