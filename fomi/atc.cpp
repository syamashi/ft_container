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

// ab,bc,caかぶりをひたすらつくる？？？

/*
.....
....
...
..
.

d=9
他5


ななめがせいぜい2個かぶり
。　　。　　。　　。　　。
　　　。　　。　　。　　。
　　　。　　。　　。　　。
。。。



。。。



。。。


。。。


ｘ・・ｘ・・ｘ・・
・・ｘ・・ｘ・・ｘ
・ｘ・・ｘ・・ｘ・
ｘ・・ｘ・・ｘ・・
これのかんかくげきあげ？？

ｘ・・・・ｘ・・・・ｘ・・・・ｘ・・・・ｘ
・・・・ｘ・・・・ｘ・・・・ｘ・・・・ｘ
・・・ｘ
・・ｘ
・ｘ

ｘ・・・ｘ・・・ｘ
・・・ｘ・・・ｘ
・・ｘ・・・ｘ
・ｘ・・・ｘ・・・
ぐうすうはかぶっちゃう

*/

void debug(){
  ll n=300;
  while(n*n<=100000){
    cout << n << ":" << n*n << endl;
    ++n;
  }
}

/*
300:90000
301:90601
302:91204
303:91809
304:92416
305:93025
306:93636
307:94249
308:94864
309:95481
310:96100
311:96721
312:97344
313:97969
314:98596
315:99225
316:99856
*/


/*
これで
・・・・ｙ・・・・ｘ
・・・ｚ・・・・ｘ
・・ｘ・・・・ｘ・・・・ｘ・・・・ｘ・・・・ｘ
・ｘ・・・・ｘ・・・・ｘ・・・・ｘ・・・・ｘ
ｘ・・・・ｘ・・・・ｘ・・・・ｘ・・・・ｘ
・・・・ｘ・・・・ｙ
・・・ｘ・・・・ｚ
・・ｘ・・・・ｘ
・ｘ・・・・ｘ
ｘ・・・・ｘ
・・・・ｘ
・・・ｘ
・・ｘ
・ｘ
ｘ


ｘ・ｘ・・ｘ・・・ｘ・・・・ｘ
・ｘ・・ｘ・・・ｘ・・・・ｘ

ー・・・・・・・
・ー・・・・・・
・・ー・・・・・
・・・ー・・・・
・・・・ー・・・
・・・・・ー・・
・・・・・・ー・
・・・・・・・ｘ

ななめとよこはＯＫっぽ
たてが個別




*/


ll qx[] = {0, 1};
ll qy[] = {10, 0};
ll qz[] = {100, 100};

int main(){
	ll V = 5;
  cincout();
  cout << V*V*V << endl;
  rep(i, V) rep(j, V) rep(k, V){
    ll x = qx[0]*i + qy[0]*j + qz[0]*k;
    ll y = qx[1]*i + qy[1]*j + qz[1]*k;
    cout << x << " " << y << endl;
  }
}