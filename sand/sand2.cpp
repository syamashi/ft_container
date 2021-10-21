#include <type_traits>
#include <iostream>
#include <vector>

template< typename T >
typename std::enable_if<std::is_integral<T>::value>::type
func(T t){
  std::cout << t << "は整数だよ" << std::endl;
}

template< typename T >
typename std::enable_if<!std::is_integral<T>::value>::type
func(T t){
  std::cout << t << "は整数じゃないよ" << std::endl;
}

int main()
{
  int a = 42;
  int b[42] = {42};
  std::vector<int> c(1, 42);

  func(1); //← 1は整数だよ
  func("a"); //← aは整数じゃないよ
  func(a); //← 42は整数だよ
  func(&a); //← 0x7ffee4af548cは整数じゃないよよ
  func(b); //← 0x7ffee4af5490は整数じゃないよ
//  func(c.begin()); // ← コンパイルエラーだけど整数じゃないよが選択される
}