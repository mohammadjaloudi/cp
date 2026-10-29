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


const int LOG = 20; // N <= 2e5

struct LCA {
    int n;
    vector<vector<int>> adj, up;
    vector<int> depth;

    LCA(int n) : n(n) {
        adj.resize(n + 1);
        up.assign(n + 1, vector<int>(LOG));
        depth.resize(n + 1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p) {
        up[u][0] = p;

        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    void build(int root = 1) {
        dfs(root, root);
    }

    int kth_ancestor(int u, int k) {
        for (int j = 0; j < LOG; j++) {
            if (k & (1 << j)) {
                u = up[u][j];
            }
        }
        return u;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        u = kth_ancestor(u, depth[u] - depth[v]);

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

    int dist(int u, int v) {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};

vector<vector<int>> adj;
vector<pair<int, int>> dp;
string s;

void dfs(int v, int p) {
    if(p != -1) dp[v] = dp[p];

    dp[v].first += (s[v - 1] == 'H');
    dp[v].second += (s[v - 1] == 'G');

    for(auto u : adj[v]) {
        if(u != p) dfs(u, v);
    }
}

void solve() {
    int n, q;
    cin >> n >> q >> s;
    adj.resize(n + 1);
    dp.resize(n + 1);

    LCA tree(n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        tree.add_edge(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
    }

    tree.build(1);
    dfs(1, -1);

    while(q--) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        int p = tree.lca(u, v);
        int h = dp[u].first + dp[v].first - 2 * dp[p].first + (s[p - 1] == 'H');
        int g = dp[u].second + dp[v].second - 2 * dp[p].second + (s[p - 1] == 'G');

        cout << ((c == 'H' && h) || (c == 'G' && g));
    }
    cout << endl;
}

int32_t main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    // cout << fixed << setprecision(7);

    int TESTCASES = 1;
    // cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
