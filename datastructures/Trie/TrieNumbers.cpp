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

struct Trie {
    struct Node {
        int child[2];
        int cnt;

        Node() {
            child[0] = child[1] = -1;
            cnt = 0;
        }
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back(); // trie.push_back(Node());
    }

    void insert(int x) {
        int node = 0;
        for(int bit = 30; bit >= 0; bit--) {
            int b = (x >> bit) & 1;

            if(trie[node].child[b] == -1) {
                trie[node].child[b] = trie.size();
                trie.emplace_back();
            }

            node = trie[node].child[b];
            trie[node].cnt++;
        }
    }

    void erase(int x) {
        int node = 0;
        for(int bit = 30; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            node = trie[node].child[b];
            trie[node].cnt--;
        }
    }

    int maxXor(int x) {
        int node = 0, ans = 0;
        for(int bit = 30; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            int c = b ^ 1;

            if(trie[node].child[c] != -1 && trie[trie[node].child[c]].cnt > 0) {
                ans |= (1LL << bit);
                node = trie[node].child[c];
            } else node = trie[node].child[b];
        }

        return ans;
    }
};

void solve() {
    int q;
    cin >> q;
    Trie trie;
    trie.insert(0);
    while(q--) {
        char c;
        int x;
        cin >> c >> x;

        if(c == '+') trie.insert(x);
        else if(c == '-') trie.erase(x);
        else cout << trie.maxXor(x) << endl;
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
