#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <typename T, typename U>
void mdebug(ft::map<T, U> const &M) {
	cout << "size:" << M.size() << endl;
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
/*
	rep(i, 20){
		int key = 0-i;
		int val = 0-i;
		cout << "--- " << "M.insert({" << key << "," << val << "})" << " ---" << endl;
		auto ret = M.insert({key, val});
		cout << " size:" << M.size() << endl;
		cout << " ret:" << ret.first->first << "," << ret.first->second << " " << ret.second << endl;
	  cout << endl;
	}
*/
}

void map_insert_delete_hardtest(){
	// 開始地点を20か所ずらして、連番で作成
	ft::map<int, int> M;
  int N=20;
  rep(i, N){ // start
    rep(j, N){
      int k=(i+j)%N;
  		M.insert({k, k});
	  	M.debug2();
    }
  	rep(j, N+10){
      int k=(i+j)%N;
      M.erase(k);
      M.debug2();
  	}
	}
}

void map2_test()
{
//	map_insert_delete_hardtest();
	map_insert_test();
}