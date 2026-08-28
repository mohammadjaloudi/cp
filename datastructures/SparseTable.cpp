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

struct SparseTable {
    int n, lg;
    vector<vector<int>> st_gcd, st_and;

    SparseTable(const vector<int>& a) {
        n = a.size();
        lg = __lg(n);
        st_gcd.assign(lg + 1, vector<int>(n));
        st_and.assign(lg + 1, vector<int>(n));
        
        for (int i = 0; i < n; i++) {
            st_gcd[0][i] = a[i];
            st_and[0][i] = a[i];
        }
        
        for (int j = 1; j <= lg; j++) {
            int len = 1 << (j - 1);
            for (int i = 0; i + (1 << j) <= n; i++) {
                st_gcd[j][i] = std::gcd(st_gcd[j - 1][i], st_gcd[j - 1][i + len]);
                st_and[j][i] = st_and[j - 1][i] & st_and[j - 1][i + len];
            }
        }
    }

    inline int get_and(int l, int r) {
        int j = __lg(r - l + 1);
        return st_and[j][l] & st_and[j][r - (1 << j) + 1];
    }

    inline int get_gcd(int l, int r) {
        int j = __lg(r - l + 1);
        return std::gcd(st_gcd[j][l], st_gcd[j][r - (1 << j) + 1]);
    }
};

void solve(){
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &i : a) cin >> i;

    SparseTable st(a);
    while(q--){
        int l, k; cin >> l >> k;
        l--;
        int left = l, right = n - 1, ans = l - 1;
        while(left <= right) {
            int mid = (left + right) / 2;

            int b = st.get_and(l, mid);
            if((b & k) == k) {
                int g = st.get_gcd(l, mid);
                if(g >= k) {
                    ans = mid;
                    left = mid + 1;
                    continue;
                }
            }
            right = mid - 1;
        }

        cout << ans - l + 1 << ' ';
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
    cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
