#include <bits/stdc++.h>
#define len(s) int(s.size())
#define all(s) s.begin(),s.end()
#define rall(s) s.rbegin(),s.rend()
#define fixed(n) fixed << setprecision(n)
#define uni(s) s.erase(unique(all(s)), s.end());
#define fi first
#define sc second
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
#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
using namespace std;

string to = "RLDU";
const int dx[] = {0, 0, 1, -1, -1, 1, -1, 1};
const int dy[] = {1, -1, 0, 0, -1, 1, 1, -1};
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ll oo = 0x3f3f3f3f;
const ll OO = 0x3f3f3f3f3f3f3f3f; 

void MO() {
	ios_base::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin),freopen("output.txt","w",stdout);
	#endif
}

signed main() {
	MO();

	
 	return 0;
}