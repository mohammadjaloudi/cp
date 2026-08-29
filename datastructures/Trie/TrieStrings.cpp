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

        // Number of strings passing through this node
        int cnt;

        // Number of strings ending at this node
        int endCnt;
        
        string bestWord;
        int bestFreq;

        Node() {
            fill(child, child + 26, -1);
            cnt = endCnt = bestFreq = 0;
            bestWord = "";
        }
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back(); // root
    }
    
    void update(string s, int freq) {
        int curr = 0;
        for(auto c : s) {
            int x = c - 'a';

            curr = trie[curr].child[x];

            if(freq > trie[curr].bestFreq) {
                trie[curr].bestFreq = freq;
                trie[curr].bestWord = s;
            }
            else if(freq == trie[curr].bestFreq) {
                if(trie[curr].bestWord.empty() ||
                s < trie[curr].bestWord) {
                    trie[curr].bestWord = s;
                }
            }
        }
    }

    void insert(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) {
                trie[curr].child[x] = trie.size();
                trie.emplace_back();
            }

            curr = trie[curr].child[x];
            trie[curr].cnt++;
        }

        trie[curr].endCnt++;
        // int freq = trie[curr].endCnt;
        // update(s, freq);
    }
    
    void erase(string s) {
        if(countExact(s) == 0) return;

        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            curr = trie[curr].child[x];
            trie[curr].cnt--;
        }

        trie[curr].endCnt--;
    }

    int countExact(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return 0;

            curr = trie[curr].child[x];
        }

        return trie[curr].endCnt;
    }

    bool search(string s) {
        return countExact(s) > 0;
    }

    bool startsWith(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return 0;

            curr = trie[curr].child[x];
        }

        return 1;
    }

    int countPrefix(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return 0;

            curr = trie[curr].child[x];
        }

        return trie[curr].cnt;
    }

    string longestExistingPrefix(string s) {
        int curr = 0;
        string ans;
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) break;

            curr = trie[curr].child[x];
            ans += c;
        }

        return ans;
    }

    string findSmallest(string s) {
        int curr = 0;
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return "";

            curr = trie[curr].child[x];
        }

        string ans = s;

        while(true) {
            if(trie[curr].endCnt > 0) return ans;

            for(int i = 0; i < 26; i++) {
                if(trie[curr].child[i] != -1) {
                    ans += char('a' + i);
                    curr = trie[curr].child[i];
                    break;
                }
            }
        }
    }

    string findLargest(string s) {
        int curr = 0;
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return "";

            curr = trie[curr].child[x];
        }

        string ans = s;

        while(true) {
            if(trie[curr].endCnt > 0) return ans;

            for(int i = 25; i >= 0; i--) {
                if(trie[curr].child[i] != -1) {
                    ans += char('a' + i);
                    curr = trie[curr].child[i];
                    break;
                }
            }
        }
    }

    string maxFreq(string s) {
        int curr = 0;
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return "";

            curr = trie[curr].child[x];
        }

        string ans = s;

        while(true) {
            int bestFreq = trie[curr].endCnt;
            int bestChild = -1;

            for(int i = 0; i < 26; i++) {
                int nxt = trie[curr].child[i];

                if(nxt == -1) continue;

                if(trie[nxt].cnt > bestFreq) {
                    bestFreq = trie[nxt].cnt;
                    bestChild = i;
                }
            }

            if(bestChild == -1) return ans;

            ans += char('a' + bestChild);
            curr = trie[curr].child[bestChild];
        }
    }

    // string mostOccurre(string s) {
    //     int curr = 0;
    //     for(char c : s) {
    //         int x = c - 'a';

    //         if(trie[curr].child[x] == -1) return "";

    //         curr = trie[curr].child[x];
    //     }

    //     string ans = s;
    //     int best = 0;

    //     function<void(int, string&)> dfs = [&](int u, string &cur) {
    //         if(trie[u].endCnt > best) {
    //             best = trie[u].endCnt;
    //             ans = cur;
    //         }

    //         for(int i = 0; i < 26; i++) {
    //             int v = trie[u].child[i];
    //             if(v == -1) continue;

    //             cur += ('a' + i);
    //             dfs(v, cur);
    //             cur.pop_back();
    //         }

    //     };

    //     string cur = s;
    //     dfs(curr, cur);

    //     return ans;
    // }

    pair<string, int> mostOccurre(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return {"", 0};

            curr = trie[curr].child[x];
        }

        return {trie[curr].bestWord, trie[curr].bestFreq};
    }

    int getFrequency(string s) {
        int curr = 0;
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1) return 0;

            curr = trie[curr].child[x];
        }
        return trie[curr].bestFreq;
    }
};

void solve() {
    int n;
    cin >> n;
    Trie trie;
    map<string, int> mp;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        trie.insert(s);
        mp[s]++;
    }

    int q;
    cin >> q;
    while(q--) {
        string s;
        cin >> s;

        auto [t, cnt] = trie.mostOccurre(s);

        if(t.empty()) cout << -1 << endl;
        else cout << t << ' ' << cnt << endl;
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
