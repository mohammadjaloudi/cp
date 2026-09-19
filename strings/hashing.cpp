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

// #define int long long
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

struct Hash {
    const long long MOD = 1e9 + 7;
    const int P = 31;
 
    int n;
    vector<int> h, p;
 
    Hash(const string &s) {
        n = s.size();
 
        h.assign(n + 1, 0);
        p.assign(n + 1, 1);
 
        for (int i = 1; i <= n; i++) {
            p[i] = 1LL * p[i - 1] * P % MOD;
        }
 
        for (int i = 0; i < n; i++) {
            int val = s[i] - 'a' + 1;
            h[i + 1] = (1LL * h[i] * P + val) % MOD;
        }
    }
 
    int getHash(int l, int r) {
        if (l > r) return 0;
        return (h[r + 1] - 1LL * h[l] * p[r - l + 1] % MOD + MOD) % MOD;
    }
};
 
void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
 
    Hash hash1(s);
    string t = s;
    reverse(t.begin(), t.end());
    Hash hash2(t);
 
    for (int i = 0; i + k <= n; i++) {
        int left1 = hash1.getHash(0, i - 1);
        int right1 = hash1.getHash(i + k, n - 1 );
        int len1 = n - (i + k);
 
        int h1 = (1LL * left1 * hash1.p[len1] + right1) % MOD;
 
        int left2 = hash2.getHash(0, n - i - k - 1);
        int right2 = hash2.getHash(n - i, n - 1);
        int len2 = i;
 
        int h2 = (1LL * left2 * hash2.p[len2] + right2) % MOD;
 
        if (h1 == h2) return void(cout << 1 << endl);
    }
 
    cout << 0 << endl;
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
