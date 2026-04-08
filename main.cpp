// #define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,lzcnt,popcnt,abm,mmx,avx,avx2,bmi,bmi2")

// typedef tree<int, null_type, less_equal<int>, rb_tree_tag, 
//              tree_order_statistics_node_update> ordered_multiset;

// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// mt19937 rnd2(chrono::steady_clock::now().time_since_epoch().count());

#define int long long
#define int64 long long
#define endl "\n"
#define pb push_back
#define all(x) x.begin(), x.end()
#define print(x) for(auto i : x) cout << i << ' ';
const double EPS = 1e-9;
long long MOD = 1e9 + 7;
long long INF = 1e18;
long long mod = 998244353;
int mx = 2e6;

int binpow(int a, int b, int m) {
    int res = 1;
    while(b) {
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
void precomp() {
    fact[0] = 1;
    for(int i = 1; i <= mx; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[mx] = binpow(fact[mx], MOD - 2, MOD);
    for(int i = mx - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
}

typedef long long i64;
// i64 binpow(__int128_t x,i64 y,i64 mod){
//     i64 ans = 1;
//     x %= mod;
//     while(y){
//         if(y & 1) ans = (x*ans)%mod;
//         y >>=1ll;
//         x = (x*x)%mod;
//     }
//     return ans;
// }
bool is_prime(i64 n){
    if(n <= 1) return 0;
    else if(n == 2) return 1;
    else if(n == 3) return 1;
    else if(!(n & 1)) return 0;
    vector<i64> bases = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022}; // 2^64
    // if number less than 2^32, {2,7,61} enough
 
    i64 d = n-1;
    int s = 0;
    while(!(d & 1)){d/=2;s++;}

    // 
    for(int a : bases){
        if(a >= n) break;
        i64 x = binpow(a,d,n);
 
 
        if(x == 1 || x == n-1) continue;
       
        bool worked = 0;
        for(int _ = 0; _ < s-1 && !worked; _++){
            x = binpow(x,2,n);
            if(x == n-1){worked = 1;break;}
        }
        
        if(!worked){
            return 0;
        }
    }
    return 1;
}

void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
              phi[j] -= phi[i];
}

struct segtree {
    int size;
    vector<int> mini;

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        mini.assign(2 * size, 0LL);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int)a.size()) mini[x] = a[lx];
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        mini[x] = min(mini[2 * x + 1], mini[2 * x + 2]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if(rx - lx == 1) {
            mini[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if(i < m) set(i, v, 2 * x + 1, lx, m);
        else set(i, v, 2 * x + 2, m, rx);
        mini[x] = min(mini[2 * x + 1], mini[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if(lx >= r || l >= rx) return INT_MAX;
        if(lx >= l && rx <= r) return mini[x];
        int m = (lx + rx) / 2;
        int s1 = calc(l, r, 2 * x + 1, lx, m);
        int s2 = calc(l, r, 2 * x + 2, m, rx);
        return min(s1, s2);
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

// void solve() {
//     int n, q;
//     cin >> n >> q;

//     segtree st;
//     st.init(n);
//     vector<int> a(n);
//     for(int i = 0; i < n; i++) cin >> a[i];
//     st.build(a);

//     while(q--) {
//         int x;
//         cin >> x;
//         if(x == 1) {
//             int i, v;
//             cin >> i >> v;
//             st.set(i, v);
//         } else {
//             int l, r;
//             cin >> l >> r;
//             cout << st.calc(l, r) << endl;
//         }
//     }
// }

struct DSU {
	vector<int>par;
	vector<vector<pair<int, int>>>cycle;
	vector<pair<int, int>>ans;
	int ncmp;
 
	void init(int n) {
		par.assign(2 * n + 10, -1);
		cycle.clear(); cycle.resize(2 * n + 10);
		ans.clear();
		ncmp = n;
	}
 
	int find(int u) {
		return par[u] < 0 ? u : par[u] = find(par[u]);
	}
 
	void join(int u, int v) {
		int a = u, b = v;
		u = find(u), v = find(v);
		if (u == v) {
			cycle[u].push_back({ a,b });
			// cout<<"please";
			return;
		}
 
		if (par[u] > par[v]) swap(u, v);
		if (v == 0)swap(u, v);
		while (!cycle[v].empty()) {
			cycle[u].push_back(cycle[v].back());
			cycle[v].pop_back();
		}
		par[u] += par[v];
		par[v] = u;
	}
	void unify(int u, int v, int p, int l) {
		v = find(v);
 
		if (!cycle[v].empty()) {
			ans.push_back(cycle[v].back()); cycle[v].pop_back();
		}
		else {
			ans.push_back({ p,l });
		}
		while (!cycle[v].empty()) {
			cycle[u].push_back(cycle[v].back());
			cycle[v].pop_back();
		}
	}
	vector<pair<int, int>> getAns() {
		return ans;
	}
};

void solve() {
    
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    // cout << fixed << setprecision(7);

    int TESTCASES = 1;
    cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
