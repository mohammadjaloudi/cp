// #define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,lzcnt,popcnt,abm,mmx,avx,avx2,bmi,bmi2")

// template <typename T>
// using ordered_set =
//     tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <typename T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ordered_set<int> st

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937 rng2(chrono::steady_clock::now().time_since_epoch().count());

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

using Matrix = vector<vector<int>>;

Matrix multiply(const Matrix &a, const Matrix &b) {
    int n = a.size();
    Matrix C(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            if(a[i][k] == 0) continue;
            for(int j = 0; j < n; j++) C[i][j] = (C[i][j] + a[i][k] * b[k][j]) % MOD;
        }
    }

    return C;
}

Matrix binpow(Matrix a, int b) {
    int n = a.size();
    Matrix res(n, vector<int> (n));
    for(int i = 0; i < n; i++) res[i][i] = 1;

    while(b) {
        if(b & 1) res = multiply(res, a);
        a = multiply(a, a);
        b >>= 1;
    }

    return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    Matrix t(n, vector<int> (n));
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t[v][u]++;
    }

    Matrix ans = binpow(t, k);

    cout << ans[n - 1][0] << endl;
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    // cout << fixed << setprecision(7);

    int TESTCASES = 1;
    // cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
