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

struct Point_map_constructer_test { double x, y; };
struct PointCmp_map_constructer_test {
    bool operator()(const Point_map_constructer_test& lhs, const Point_map_constructer_test& rhs) const { 
        return lhs.x < rhs.x; // NB. intentionally ignores y
    }
};

void map_constructer_test()
{
	pout("map_constructer_test");

 // (1) Default constructor
  ft::map<std::string, int> map1;
  map1["something"] = 69;
  map1["anything"] = 199;
  map1["that thing"] = 50;


  cout << "map1 = ";
  mdebug(map1);


  // (2) Range constructor
  ft::map<std::string, int> iter(map1.find("anything"), map1.end());
  cout << "\niter = "; mdebug(iter);
  cout << "map1 = "; mdebug(map1);
 
  // (3) Copy constructor
  ft::map<std::string, int> copied(map1);
  cout << "\ncopied = "; mdebug(copied);
  cout << "map1 = "; mdebug(map1);
 
  // Custom Key class option 1:
  // Use a comparison struct
  ft::map<Point_map_constructer_test, double, PointCmp_map_constructer_test> mag;
  mag[{5, -12}] = 13;
  mag[{3, 4}] = 5;
  mag[{-8, -15}] = 17;
 
  for(auto p : mag)
      cout << "The magnitude of (" << p.first.x
                << ", " << p.first.y << ") is "
                << p.second << '\n';
 
  // Custom Key class option 2:    
  // Use a comparison lambda
  // This lambda sorts points according to their magnitudes, where note that
  //  these magnitudes are taken from the local variable mag
  auto cmpLambda = [&mag](const Point_map_constructer_test &lhs, const Point_map_constructer_test &rhs) { return mag[lhs] < mag[rhs]; };
  //You could also use a lambda that is not dependent on local variables, like this:
  //auto cmpLambda = [](const Point &lhs, const Point &rhs) { return lhs.y < rhs.y; };
  ft::map<Point_map_constructer_test, double, decltype(cmpLambda)> magy(cmpLambda);
 
  //Various ways of inserting elements:
  magy.insert(std::pair<Point_map_constructer_test, double>({5, -12}, 13));
  magy.insert({ {3, 4}, 5});
  magy.insert({Point_map_constructer_test{-8.0, -15.0}, 17});
 
  cout << '\n';
  for(auto p : magy)
      cout << "The magnitude of (" << p.first.x
                << ", " << p.first.y << ") is "
                << p.second << '\n';

}

void map_test()
{
	map_constructer_test();

}
