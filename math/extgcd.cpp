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

// recursive
int gcd_(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd_(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

void solve() {
    int a, b;
    while((cin >> a >> b)) {
        int n = gcd(a, b);
        
        // iterative

        bool a1 = (a < 0);
        bool b1 = (b < 0);
        a = abs(a);
        b = abs(b);

        int x0 = 1, y0 = 0;
        int x1 = 0, y1 = 1;
    
        while(b) {
            int q = a / b;
            int r = a % b;
    
            a = b;
            b = r;
    
            int next_x = x0 - q * x1;
            x0 = x1;
            x1 = next_x;
    
            int next_y = y0 - q * y1;
            y0 = y1;
            y1 = next_y;
        }
    
        int x = x0, y = y0;
        x = x * (a1? -1 : 1);
        y = y * (b1? -1 : 1);
        cout << x << ' ' << y << ' ' << a << endl;
        // a = n (gcd(a, b)) when the loop ends

        // int x, y;
        // int g = gcd_(abs_a, abs_b, x, y);
    }
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
