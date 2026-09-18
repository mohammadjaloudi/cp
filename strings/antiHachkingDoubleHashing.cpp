#define _CRT_SECURE_NO_WARNINGS
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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
    const long long MOD1 = 1'000'000'007;
    const long long MOD2 = 1'000'000'009;
    const long long P = uniform_int_distribution<long long>(256, MOD1 - 2)(rng);

    int n;
    vector<int> p1, p2;
    vector<int> h1, h2;

    Hash(const string &s) {
        n = s.size();

        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);

        int curr1 = 1, curr2 = 1;
        for(int i = 1; i <= n; i++) {
            curr1 = 1LL * curr1 * P % MOD1;
            curr2 = 1LL * curr2 * P % MOD2;

            p1[i] = curr1;
            p2[i] = curr2;
        }

        for(int i = 0; i < n; i++) {
            int val = s[i] - 'a' + 1;
            h1[i + 1] = (1LL * h1[i] * P + val) % MOD1;
            h2[i + 1] = (1LL * h2[i] * P + val) % MOD2;
        }
    }

    pair<int, int> getHash(int l, int r) {
        int len = r - l + 1;
        int x1 = (h1[r + 1] - 1LL * h1[l] * p1[len] % MOD1 + MOD1) % MOD1;
        int x2 = (h2[r + 1] - 1LL * h2[l] * p2[len] % MOD2 + MOD2) % MOD2;

        return {x1, x2};
    }

    bool equal(int l1, int r1, int l2, int r2) {
        if(r1 - l1 != r2 - l2) return 0;
        return getHash(l1, r1) == getHash(l2, r2);
    }
};

void solve() {
    string s;
    cin >> s;
    
    Hash hash(s);
    
    int n = s.size();
    for(int i = 0; i < n - 1; i++) {
        if(hash.equal(0, i, n - i - 1, n - 1)) cout << i + 1 << ' ';
    }
    cout << endl;
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
