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
#define print(x) for(auto i : x) cout << i + 1 << ' ';
const double EPS = 1e-9;
long long MOD = 1e9 + 7;
long long INF = 1e18;
long long mod = 998244353;
int mx = 2e6;

// a class to make Strongly connected component objects
class SCC {
    private:
        int n, time, cnt;
        // n: number of nodes
        // time: represints the id of each node
        // cnt: number of SCC
        vector<vector<int>> adj;
        // adj list to build the graph
    

        // this a dfs
        void dfs(int u, vector<int> &id, vector<int> &low, stack<int> &st, vector<bool> &onStack, vector<vector<int>>& scc) {
            // mark the id and the lowest possible value as uique
            id[u] = low[u] = ++time;
            st.push(u); // push the node into the stack
            onStack[u] = 1; // if yes then we can do low[u] = min(low[u], id[v]);

            for(auto v : adj[u]) {
                if(id[v] == -1) { // not visited yet
                    dfs(v, id, low, st, onStack, scc);
                    low[u] = min(low[u], low[v]); // min between me and where I came from (backtrack without dfs2)
                } else if(onStack[v]) low[u] = min(low[u], id[v]); // min between taking me and the id of the other node
            }

            // if low me = id me then I'm the beginning of this SCC
            if(low[u] == id[u]) {
                vector<int> curr; // to push all the nodes here
                int w = -1;
                do {
                    w = st.top();
                    st.pop();
                    onStack[w] = 0;
                    curr.pb(w);
                } while(w != u);
                scc.pb(curr);
                cnt++;
            }
        }

    public:
        SCC(int m) {
            n = m;
            adj.resize(n);
            time = cnt = 0;
        } // initialization

        void addEdge(int u, int v) {adj[--u].pb(--v);} // add edge in the adj

        int getSz() {return cnt;} // get the number of SCC

        vector<vector<int>> findSCC() {
            vector<int> id(n, -1), low(n, -1);
            // id: the components id = time
            // low: the lowest value in this SCC
            // low[i] = low[j] -> i and j are in the same SCC
            vector<bool> onStack(n); // can I take you as min value?
            stack<int> st; // remove the values from the onStack
            vector<vector<int>> scc; // all the SCC

            for(int i = 0; i < n; i++) {
                if(id[i] == -1) dfs(i, id, low, st, onStack, scc);
            }

            return scc;
        }
};

void solve() {
    // problem:
    // given a directed graph
    // find number of SCC and the maximum sized SCC, there're multiple answers
    int n, m;
    cin >> n >> m;
    
    SCC g(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    vector<vector<int>> a = g.findSCC();

    cout << g.getSz() << endl;
    vector<int> b;
    int mx = 0;
    for(int i = 0; i < a.size(); i++) {
        if(a[i].size() > mx) {
            mx = a[i].size();
            b = a[i];
        }
    }
    print(b)
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
