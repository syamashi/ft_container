#include <cassert>

constexpr int square(int x)
{
  return x * x;
}

int main()
{
  constexpr int compile_time_result = square(3);
  static_assert(compile_time_result == 9, "result must be 9"); // compile error

  int runtime_result = square(3);
  assert(runtime_result == 9);
}
