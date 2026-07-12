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

vector<int> pref_function(string &s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for(int i = 1; i < n; i++) {
        int j = pi[i - 1];
        
        while(j > 0 && s[i] != s[j]) j = pi[j - 1];
        
        j += (s[i] == s[j]);
        
        pi[i] = j;
    }
    return pi;
}

int count(string &s, string &t) {
    string u = t + '#' + s;
    vector<int> pi = pref_function(u);

    // vector<int> matches;
    int len = t.size(), ans = 0, n = u.size();
    for(int i = 0; i < n; i++) {
        if(pi[i] == len) {
            // Match found! Calculate the starting 0-based index in the original text
            // matches.pb(i - 2 * len);
            ans++;
        }
    }
    return ans;
}

// A string S has a period P if it can be formed by repeating P multiple times.
// For example, the string ababab has a period of ab (length 2).

// we call the string we want to find the rpeats inside it
// for example we want to find for s = ababab
// we just call get_shortest_period(ababab)
int get_shortest_period(string &s) {
    vector<int> pi = pref_function(s);
    int n = s.size();
    int len = n - pi[n - 1];
    
    // If the remaining length divides the total length evenly, it's a valid period
    if (n % len == 0) return len;
    
    // Otherwise, the shortest period is the string itself
    return n; 
}

void solve() {
    string s, t;
    cin >> s >> t;

    // cout << count(s, t) << endl;
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
