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
        int child[26];
        int cnt;
        bool isEnd;

        Node() {
            fill(child, child + 26, -1);
            cnt = 0;
            isEnd = 0;
        }
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back(); // root
    }

    void insert(string s) {
        int curr = 0;
        for(auto c : s) {
            int x = c - 'a';
            if(trie[curr].child[x] == -1) {
                trie[curr].child[x] = trie.size();
                trie.emplace_back();
            }

            curr = trie[curr].child[x];
            trie[curr].cnt++;
        }

        trie[curr].isEnd = 1;
    }

    bool search(string s) {
        int curr = 0;
        for(auto c : s) {
            int x = c - 'a';
            if(trie[curr].child[x] == -1) return 0;

            curr = trie[curr].child[x];
        }

        return trie[curr].isEnd;
    }

    bool startsWith(string s) {
        int curr = 0;
        for(auto c : s) {
            int x = c - 'a';
            if(trie[curr].child[x] == -1) return 0;

            curr = trie[curr].child[x];
        }

        return 1; // if we wanted just to check true / false
    }

    int countPrefix(string s) {
        int cur = 0;

        for (char c : s) {
            int x = c - 'a';

            if (trie[cur].child[x] == -1)
                return 0;

            cur = trie[cur].child[x];
        }

        return trie[cur].cnt;
    }

    string longestExistingPrefix(string s) {
        int curr = 0;
        string ans = "";

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                break;

            curr = trie[curr].child[x];
            ans += c;
        }

        return ans; // ans.size() and type of function int if we wanted the length
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    Trie trie;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        trie.insert(s);
    }

    while(q--) {
        string s;
        cin >> s;
        int ans = trie.countPrefix(s);
        cout << ans << endl;
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
