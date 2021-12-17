#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

void is_integral_test() {
  pout("is_integral_test");
  
  cout << ft::is_integral<int>::value << ":int is integral" << endl;
  cout << ft::is_same<ft::is_integral<int>::value_type, bool>::value << ":value_type == bool" << endl;
  cout << ft::is_same<ft::is_integral<int>::type, ft::true_type>::value << ":type == true_type" << endl;
//  cout << ft::is_integral<int>() << ":is_integral<int>() == true" << endl;

  cout << ft::is_integral<int*>::value << ":value == false, int* is not integral" << endl;
  cout << ft::is_same<ft::is_integral<int*>::value_type, bool>::value << ":value_type == bool" << endl;
  cout << ft::is_same<ft::is_integral<int*>::type, ft::false_type>::value << ":type == false_type" << endl;
//  cout << ft::is_integral<int*>() << ":is_integral<int*>() == false" << endl;

  cout << ft::is_integral<bool>::value << ":bool is integral" << endl;
  cout << ft::is_integral<char>::value << ":char is integral" << endl;
  cout << ft::is_integral<char32_t>::value << ":char32_t is integral" << endl;
  cout << ft::is_integral<const long long>::value << ":const long long is integral" << endl;
  cout << ft::is_integral<volatile unsigned>::value << ":volatile unsigned is integral" << endl;

  enum my_enum {};
  cout << ft::is_integral<my_enum>::value << ":my_enum is not integral" << endl;
  cout << ft::is_integral<int&>::value << ":int& is not integral" << endl;
  cout << ft::is_integral<int[1]>::value << ":int[1] is not integral" << endl;
  cout << ft::is_integral<int()>::value << ":int () is not integral" << endl;
  cout << ft::is_integral<float>::value << ":float is not integral" << endl;

  cout << ft::is_integral<bool>::value << ":bool is integral" << endl;
  cout << ft::is_integral<char>::value << ":char is integral" << endl;
  cout << ft::is_integral<char16_t>::value << ":char16 is integral" << endl;
  cout << ft::is_integral<char32_t>::value << ":char32 is integral" << endl;
  cout << ft::is_integral<wchar_t>::value << ":wchar is integral" << endl;
  cout << ft::is_integral<short>::value << ":short is integral" << endl;
  cout << ft::is_integral<int>::value << ":int is integral" << endl;
  cout << ft::is_integral<long>::value << ":long is integral" << endl;
  cout << ft::is_integral<long long>::value << ":longlong is integral" << endl;

  cout << ft::is_integral<ft::vector<int>::iterator>::value << ":V.end() is not integral" << endl;

  ft::is_integral<int> F;
  int f = F();
  cout << f << endl;
}

void util_test(){
  is_integral_test();
}