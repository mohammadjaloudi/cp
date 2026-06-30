// #define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,lzcnt,popcnt,abm,mmx,avx,avx2,bmi,bmi2")

// typedef tree<int, null_type, less_equal<int>, rb_tree_tag, 
//              tree_order_statistics_node_update> ordered_multiset;

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

// merge sort tree
class MergeSortTree {
    private:
        int n; // size of the tree
        vector<vector<int>> tree; // here we have 2d vector cuz we have to do something like this
        /*
        7 | 12 | 8 | 6 | 9 | 1 | 4 | 3 | 5 | 10 | 11 | 2

            7 |  8,12  | 6 |  1,9  | 4 |  3,5  | 10 | 2,11

            7,8,12   |   1,6,9   |   3,4,5   | 2,10,11

                1,6,7,8,9,12     |    2,3,4,5,10,11

                    1,2,3,4,5,6,7,8,9,10,11,12
        */

        // here we have the elements 
        // we make the childs of size 1
        // then we merge the sorted vectors
        // at the end we have the sorted array
        // here we can qeury for example [l, r]
        // lets splie [l, r] into : [l1, r1] + [l2 = r1 + 1, r2] + [l3 = r2 + 1, r3]
        // in the range [l2, r2] we have a full 2^x size
        // so we can query it alone: for example [2, 6]
        // here we'll see the [a, b, c, d] sorted
        // get the first element = k
        // all of elements before it are < k
        // but in reality we do this:
        // [l, mid] + [mid + 1, r]
        // and solve it
        // just like segment tree
    
    public:
        MergeSortTree(vector<int>& a) { // constructor to initialize the objects
            n = a.size();
            tree.resize(4 * n); // O(n log (n)) space
            build(1, 0, n - 1, a);
        }

        // O(n * log (n))
        // build function
        void build(int node, int start, int end, vector<int> &a) {
            if(start == end) { // if we reach the child we add it as a single element
                tree[node].pb(a[start]);
                return;
            }

            int mid = start + (end - start) / 2;
            int left = 2 * node;
            int right = 2 * node + 1;

            build(left, start, mid, a);
            build(right, mid + 1, end, a);

            // merge the sorted vectors so we have the built merge sort tree
            merge(all(tree[left]), all(tree[right]), back_inserter(tree[node]));
        }

        // O(log ^ 2 (n))
        // query for number of elements < k in the range [l, r]
        int query(int node, int start, int end, int l, int r, int k) {
            if(r < start || end < l) return 0;

            if(l <= start && end <= r) {
                auto it = lower_bound(all(tree[node]), k);
                return distance(tree[node].begin(), it);
            }

            int mid = start + (end - start) / 2;
            int left = 2 * node;
            int right = 2 * node + 1;

            int p1 = query(left, start, mid, l, r, k);
            int p2 = query(right, mid + 1, end, l, r, k);

            return p1 + p2;
        }

        int query(int l, int r, int k) {
            return query(1, 0, n - 1, l, r, k);
        }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    MergeSortTree mst(a);

    while(q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;

        l--;
        r--;

        int right = mst.query(l, r, y + 1); // elements <= y
        int left = mst.query(l, r, x); // elements < x

        cout << right - left << endl; // [x, y] in the range [l, r]
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
