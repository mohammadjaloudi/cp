// #define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
using namespace std;

// typedef tree<int, null_type, less_equal<int>, rb_tree_tag, 
//              tree_order_statistics_node_update> ordered_multiset;

// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// mt19937 rnd2(chrono::steady_clock::now().time_since_epoch().count());

#define int long long
#define ll long long
#define int64 long long
#define endl "\n"
#define pb push_back
#define all(x) x.begin(), x.end()
#define print(x) for(auto i : x) cout << i << ' ';
ll MOD = 1e9 + 7;
ll INF = 1e18;
ll mod = 998244353;
int mx = 1e6;
vector<int> fact(mx + 1), inv(mx + 1);
 
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

long long C[35][35];
 
void precompute2() {
    for (int i = 0; i <= 34; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

void solve() {
    
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    precomp();

    // cout << fixed << setprecision(2);

    int TESTCASES = 1;
    cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
