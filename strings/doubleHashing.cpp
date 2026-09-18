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

struct Hash {
    const long long P = 53; // 31 or 53 or 911382323 or 911382
    const long long MOD1 = 1'000'000'007;
    const long long MOD2 = 1'000'000'009;

    int n;

    vector<int> prefix1, prefix2;
    vector<int> powers1, powers2;
    
    Hash(const string &s) {
        n = s.size();
    
        prefix1.assign(n + 1, 0);
        prefix2.assign(n + 1, 0);

        powers1.assign(n + 1, 1);
        powers2.assign(n + 1, 1);
    
        int p1 = 1, p2 = 1;
        for(int i = 1; i <= n; i++) {
            p1 = 1LL * p1 * P % MOD1;
            p2 = 1LL * p2 * P % MOD2;

            powers1[i] = p1;
            powers2[i] = p2;
        }

        for(int i = 0; i < n; i++) {
            int val = s[i] - 'a' + 1;
            prefix1[i + 1] = (1LL * prefix1[i] * P + val) % MOD1;
            prefix2[i + 1] = (1LL * prefix2[i] * P + val) % MOD2;
        }
    }
    
    pair<int, int> getHash(int l, int r) {
        int len = r - l + 1;
        int x1 = (prefix1[r + 1] - 1LL * prefix1[l] * powers1[len] % MOD1 + MOD1) % MOD1;
        int x2 = (prefix2[r + 1] - 1LL * prefix2[l] * powers2[len] % MOD2 + MOD2) % MOD2;

        return {x1, x2};
    }

    bool equal(int l1, int r1, int l2, int r2) {
        if(r1 - l1 + 1 != r2 - l2 + 1) return 0;
        return getHash(l1, r1) == getHash(l2, r2);
    }
};


void solve() {
    string s, t;
    cin >> s >> t;
    
    Hash h1(s), h2(t);
    auto a = h2.getHash(0, (int)t.size() - 1);
    int ans = 0;

    for(int i = 0; i <= (int)s.size() - (int)t.size(); i++) {
        auto x = h1.getHash(i, i + (int)t.size() - 1);
        ans += (x == a);
    }

    cout << ans << endl;
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
