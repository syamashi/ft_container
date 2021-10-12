#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
using pll=pair<ll, ll>;
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

ll MOD = 1e9+7;
ll modpow(ll a, ll n){ if (n==0) return 1; if (n%2==1) return (a * modpow(a, n - 1)) % MOD;  else { ll t = modpow(a, n / 2) % MOD; return (t * t) % MOD; } }
ll modinv(ll n){ return modpow(n, MOD-2); }
ll dx[] = {0, 1, 0, -1};
ll dy[] = {-1, 0, 1, 0};
  
//priority_queue<ll, vector<ll>, greater<ll>> Q;

//    size_t = 18446744073709551615 (1.8*10^19)
// LLONG_MAX = 9223372036854775807 (9.2*10^18)
//   INT_MAX = 2147483647 (2.1*10^9)
/*

*/

bool B[12000][12000];
int main(){
  cincout();

  ll N;
  cin >> N;
  set<ll> X;
  set<ll> Y;
  set<ll> XY;
  set<ll> YX;
  rep(i, N){
    ll x, y;
    cin >> x >> y;
    X.insert(x);
    Y.insert(x);
    XY.insert(x-y);
    YX.insert(x+y);
    B[x][y] = true;
  }
  cout << X.size() << " " << Y.size() << " " << XY.size() << " " << YX.size() << endl;

  ll V=20;
  for(ll i=V-1; i>=0; --i){
	  rep(j, V){
		  if (B[i][j]) cout << "ｘ";
		  else cout << "・";
	  }
	  cout << endl;
  }
}
