#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifndef ONLINE_JUDGE
    #include "library/debug.h"
#else
    #define debug(...)
#endif

#define len(s) int(s.size())
#define all(s) s.begin(),s.end()
#define rall(s) s.rbegin(),s.rend()
#define fixed(n) fixed << setprecision(n)
#define uni(s) s.erase(unique(all(s)), s.end());
#define fi first
#define sc second
#define ld long double
#define ll long long int
#define endl '\n'
#define yes(b) (b ? "YES" : "NO")
#define yes2(b) (b ? "Yes" : "No")
#define SUM(v) accumulate(all(v), 0LL)
#define pqueue priority_queue
#define MIN(c) vector<c>, greater<c>
#define ON(n, bit) ((n) | (1LL << bit))
#define OFF(n, bit) ((n) & ~(1LL << bit))
#define isON(n, bit) (((n) >> (bit)) & 1)
#define tog(n, bit) ((n) ^ (1LL << (bit - 1LL)))
#define log(b, r) log(r) / log(b)
#define ull unsigned long long
#define popcount __builtin_popcount
#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<>, rb_tree_tag,tree_order_statistics_node_update>// set
typedef tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_multiset;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll a, ll b) {
    return uniform_int_distribution<ll>(a, b)(rng);
}
 


string to = "RLDU";
const int dx[] = {0, 0, 1, -1, -1, 1, -1, 1};
const int dy[] = {1, -1, 0, 0, -1, 1, 1, -1};
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ll oo = 0x3f3f3f3f;
const ll OO = 0x3f3f3f3f3f3f3f3f; 
const ld EPS = 1e-9;

void MO() {
	ios_base::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin),freopen("output.txt","w",stdout);
	#endif
}

template < typename T = int> istream& operator >> (istream &in, vector < T > &v) {
	for (auto &x : v) in >> x;
	return in;
}

template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) {
	for (const T &x : v) out << x << ' ';
	return out;
}

ll fastpower(ll x , ll n) {
	ll result = 1;
	while(n) {
		if(n % 2 == 1) result *= x;

		x *= x;
		n = n / 2;
	}
	return result;
}

ll fastpowermod(ll x , ll n , ll m) {
	ll result = 1;
	while(n) {
		if(n % 2 == 1) result = ((result % m) * (x % m)) % m;

		x = ((x % m) * (x % m)) % m;
		n = n / 2;
	}
	return result;
}

ll add(ll a , ll b , ll m = mod) { return ( (a % m) + (b % m) ) % m; }
ll sub(ll a , ll b , ll m = mod) { return ( ((a % m) - (b % m) % m) + m ) % m; }
ll mul(ll a , ll b , ll m = mod) { return ( (a % m) * (b % m) ) % m; }
ll div(ll a, ll b, ll m = mod) { return mul(a, fastpowermod(b, m - 2, m), m); }
ll fixmod(ll a, ll m = mod) { return (a % m + m) % m; }
ll fist_num_bigger_than_x_mod(ll n, ll mod) { return ((n + mod - 1)  / mod ) * mod; }

signed main() {
	MO();

	
 	return 0;
}