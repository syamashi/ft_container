#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
using pll=pair<ll, ll>;
using tll = tuple<ll, ll, ll>;
#define rep(i,n) for (ll i=0; i<n; ++i)
#define all(c) begin(c),end(c)
#define PI acos(-1)
#define oo 2e18
void cincout(){ cin.tie(0); ios::sync_with_stdio(0); cout << fixed << setprecision(10); }
template<typename T1, typename T2>
bool chmax(T1 &a,T2 b){if(a<b){a=b;return true;}else return false;}
template<typename T1, typename T2>
bool chmin(T1 &a,T2 b){if(a>b){a=b;return true;}else return false;}
ld dist(ld x1,ld x2,ld y1,ld y2){return (sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));}
constexpr const ll MOD = 1e9+7;
ll modpow(ll a, ll n){ if (n==0) return 1; if (n%2==1) return (a * modpow(a, n - 1)) % MOD;  else { ll t = modpow(a, n / 2) % MOD; return (t * t) % MOD; } }
ll modinv(ll n){ return modpow(n, MOD-2); }
// 逆元（modが素数以外）https://atcoder.jp/contests/abc186/tasks/abc186_e
ll modinv2(ll a, ll m) { // ret = inv(a) mod m
  ll b=m, u=1, v=0; while (b){ ll t=a/b; a-=t*b; swap(a, b); u-=t*v; swap(u, v); } u%=m; if (u<0) u+=m; return u; }
// 座標圧縮
template<typename T>
ll comp(vector<T> &A){ map<T, ll> mp; for(auto p: A) mp[p] = 0; ll sz = 0; for(auto &p: mp) p.second = ++sz; for(auto &a: A) a = mp[a]; return sz; }
ll dx[] = {0, 1, 0, -1};
ll dy[] = {-1, 0, 1, 0};  
bool is_pop(ll hash, ll d){ return (hash>>d)&1; }
//priority_queue<ll, vector<ll>, greater<ll>> Q;

//    size_t = 18446744073709551615 (1.8*10^19)
// LLONG_MAX = 9223372036854775807 (9.2*10^18)
//   INT_MAX = 2147483647 (2.1*10^9)
/*

*/


template <typename pval>
struct node{
	pval v;
	void testout(){
		cout << "first:" << v.first << " second:" << v.second << endl;
	}
};

template<typename pval>
class tree_iterator{
	typedef node<pval> _Link_type;

	pval p;
};

template<typename key, typename pval>
class tree{
	typedef tree_iterator<pval> iterator;
};

template<typename key, typename tp>
class mp{
	typedef std::pair<const key, tp> pvalue_type;
	typedef tree<key, pvalue_type> rep_type;
	typedef typename rep_type::iterator iterator;
};

template<typename T>
struct f{
	typedef f<T> F;
	F x;
};

int main(){
  cincout();
  {
	  pair<int, int> P{2, 3};
	  mp<int, int> M;
	  mp<int, int>::iterator it;
	  
  }
}