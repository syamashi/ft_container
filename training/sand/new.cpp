#include <memory>
#include <iostream>
#include <algorithm>
#include <numeric>

struct S{
  const int* a;
  const int  b;
  S(): b(10){}
  void outs(){
    std::cout << "*a:" << *a << std::endl;
    std::cout << "b:" << b << std::endl;
  }
};

int main(){
  std::allocator<S> al;
  std::allocator<S>::pointer p = al.allocate(1);
  std::allocator<const int*> al2;
  std::allocator<const int*>::pointer p2 = al2.allocate(1);

  S s;
  const int n=3;
  const int* c = &n;

 // al.construct(p, s);
  al2.construct(p2, c);
  std::cout << "**p2:" << *(*p2) << std::endl ;
  p->a = *p2;
  p->outs();

//  al.deallocate(p, 1);
  al2.deallocate(p2, 1);
  return 0;
}