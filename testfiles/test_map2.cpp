#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <typename T>
void mdebug(T &V) {
	cout << "size:" << V.size() << endl;
	/*
  for (auto it = V.begin(); it != V.end(); ++it){
    cout << "M["(*it).first << "]:" << (*it).second << endl;
  }
 for(auto v: V){
	 cout << v.first << " " << v.second << endl;
 }
  */
  cout << endl;
}

template < typename Iterator >
void itdebug( Iterator first, Iterator last )
{
	cout << "{";
    for ( auto iter = first ; iter != last ; ++iter ){
		if(iter != first) cout << " ";
        cout << *iter ;
	}
	cout << "}" << endl;
}


void map_insert_test(){
	pout("map_insert_test");

	ft::map<int, int> M;
}

void map2_test()
{
	map_insert_test();
}