#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <class T>
void vdebug(T &V) {
	cout << "size:" << V.size() << " capacity:" << V.capacity() << endl;
	cout << "{ ";
  for (typename T::iterator it = V.begin(); it != V.end(); ++it) cout << *it << " ";
  cout << "}" << endl;
}

void stack_constructer_test()
{
	pout("stack_constructer_test");
  ft::vector<int> myvector (2,200);        // vector with 2 elements

  ft::stack<int> first;                    // empty stack

  ft::stack<int,ft::vector<int> > third;  // empty stack using vector
  ft::stack<int,ft::vector<int> > fourth (myvector);

  cout << "size of first: " << first.size() << '\n';
  cout << "size of third: " << third.size() << '\n';
  cout << "size of fourth: " << fourth.size() << '\n';
}

void stack_empty_test()
{
	pout("stack_empty_test");
  ft::stack<int> mystack;
  int sum (0);

  for (int i=1;i<=10;i++) mystack.push(i);

  while (!mystack.empty())
  {
     sum += mystack.top();
     mystack.pop();
  }

  cout << "total: " << sum << '\n';
}

void stack_size_test()
{
	pout("stack_size_test");
  ft::stack<int> myints;
  cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  cout << "2. size: " << myints.size() << '\n';
}

void stack_top_test()
{
	pout("stack_top_test");
  ft::stack<int> mystack;

//  cout << "mystack.top() is now " << mystack.top() << '\n'; // Segmentation fault

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  cout << "mystack.top() is now " << mystack.top() << '\n';

}

void stack_push_test()
{
	pout("stack_push_test");

  ft::stack<int> mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  cout << "Popping out elements...";
  while (!mystack.empty())
  {
     cout << ' ' << mystack.top();
     mystack.pop();
  }
  cout << '\n';	
}

void stack_nonmember_operator_test()
{
	pout("stack_nonmember_operator_test");

    ft::stack<int> alice;
	rep(i, 3) alice.push(i+1);
    ft::stack<int> bob;
	rep(i, 4) bob.push(i+7);
    ft::stack<int> eve(alice);
 
    cout << std::boolalpha;
 
    // Compare non equal containers
    cout << "alice == bob returns " << (alice == bob) << '\n';
    cout << "alice != bob returns " << (alice != bob) << '\n';
    cout << "alice <  bob returns " << (alice < bob) << '\n';
    cout << "alice <= bob returns " << (alice <= bob) << '\n';
    cout << "alice >  bob returns " << (alice > bob) << '\n';
    cout << "alice >= bob returns " << (alice >= bob) << '\n';
 
    cout << '\n';
 
    // Compare equal containers
    cout << "alice == eve returns " << (alice == eve) << '\n';
    cout << "alice != eve returns " << (alice != eve) << '\n';
    cout << "alice <  eve returns " << (alice < eve) << '\n';
    cout << "alice <= eve returns " << (alice <= eve) << '\n';
    cout << "alice >  eve returns " << (alice > eve) << '\n';
    cout << "alice >= eve returns " << (alice >= eve) << '\n';

}

void stack_test()
{
	stack_constructer_test();
	stack_empty_test();
	stack_size_test();
	stack_top_test();
	stack_push_test();
	stack_nonmember_operator_test();
}