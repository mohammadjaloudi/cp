// #define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,lzcnt,popcnt,abm,mmx,avx,avx2,bmi,bmi2")

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

// Lazy Segment Tree to track minimum bank balance across ranges
struct SegTree {
    int n;
    vector<int> tree, lazy;

    SegTree(int size) {
        n = size;
        // 4 * n is the standard safe size for a segment tree
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    // Push the "sticky notes" (lazy values) down to the children
    void push(int node) {
        if (lazy[node] != 0) {
            tree[2 * node] += lazy[node];
            lazy[2 * node] += lazy[node];
            tree[2 * node + 1] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    // Range addition/subtraction
    void update(int node, int start, int end, int l, int r, int val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            tree[node] += val;
            lazy[node] += val;
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    // Range Minimum Query
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INF; // Return infinity if out of bounds
        if (l <= start && end <= r) return tree[node];
        
        push(node);
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return min(p1, p2);
    }
};

void solve() {
    int n, x;
    cin >> n >> x;
    
    vector<pair<int, int>> a(n);
    SegTree st(n);
    
    for(int i = 0; i < n; i++) {
        int c;
        cin >> c;
        a[i] = {c, i}; // Store {cost, original_month_index}
        
        // Initialize the tree with the max money we have at month i.
        // Because we can only spend money earned in PREVIOUS months,
        // at month 'i' (0-indexed), we have exactly i * x money available.
        st.update(1, 0, n - 1, i, i, i * x);
    }

    // YOUR IDEA: Process the cheapest items first!
    sort(all(a));

    int ans = 0;
    for(int i = 0; i < n; i++) {
        int cost = a[i].first;
        int idx = a[i].second;

        // Check the lowest bank balance we will have from 'idx' up to the end of time (n - 1)
        int min_future_money = st.query(1, 0, n - 1, idx, n - 1);

        // If spending 'cost' right now doesn't put our bottleneck month below 0...
        if(min_future_money >= cost) {
            ans++;
            
            // ...then we buy it! Deduct the cost from our balance for this month 
            // AND all future months.
            st.update(1, 0, n - 1, idx, n - 1, -cost);
        }
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
    cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
