// stack::push/pop
#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <set>
#include <map>

int main ()
{
  std::stack<int> mystack;
  std::stack<int> mystack2;

  mystack == mystack2;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';


  std::set<int> S;
  std::map<int, int> MP;
  
  return 0;
}