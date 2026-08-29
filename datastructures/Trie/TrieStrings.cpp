#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct Trie {

    struct Node {
        int child[26];

        // Number of strings passing through this node
        int cnt;

        // Number of strings ending at this node
        int endCnt;

        Node() {
            fill(child, child + 26, -1);
            cnt = 0;
            endCnt = 0;
        }
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back(); // root
    }

    // =========================================================
    // INSERT
    // =========================================================

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
    }

    // =========================================================
    // ERASE
    // =========================================================

    void erase(string s) {
        if(countExact(s) == 0)
            return;

        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            curr = trie[curr].child[x];
            trie[curr].cnt--;
        }

        trie[curr].endCnt--;
    }

    // =========================================================
    // COUNT EXACT
    // =========================================================

    int countExact(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                return 0;

            curr = trie[curr].child[x];
        }

        return trie[curr].endCnt;
    }

    // =========================================================
    // SEARCH
    // =========================================================

    bool search(string s) {
        return countExact(s) > 0;
    }

    // =========================================================
    // STARTS WITH
    // =========================================================

    bool startsWith(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                return false;

            curr = trie[curr].child[x];
        }

        return true;
    }

    // =========================================================
    // COUNT PREFIX
    // =========================================================

    int countPrefix(string s) {
        int curr = 0;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                return 0;

            curr = trie[curr].child[x];
        }

        return trie[curr].cnt;
    }

    // =========================================================
    // LONGEST EXISTING PREFIX
    // =========================================================

    string longestExistingPrefix(string s) {
        int curr = 0;
        string ans;

        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                break;

            curr = trie[curr].child[x];
            ans += c;
        }

        return ans;
    }

    // =========================================================
    // SMALLEST WORD WITH PREFIX
    // =========================================================

    string findSmallest(string s) {
        int curr = 0;

        // Go to the prefix
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                return "";

            curr = trie[curr].child[x];
        }

        string ans = s;

        while(true) {

            // Current prefix itself is a word
            if(trie[curr].endCnt > 0)
                return ans;

            // Try a -> z
            for(int i = 0; i < 26; i++) {

                if(trie[curr].child[i] != -1) {
                    ans += char('a' + i);
                    curr = trie[curr].child[i];
                    break;
                }
            }
        }
    }

    // =========================================================
    // LARGEST WORD WITH PREFIX
    // =========================================================

    string findLargest(string s) {
        int curr = 0;

        // Go to the prefix
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                return "";

            curr = trie[curr].child[x];
        }

        string ans = s;

        while(true) {

            if(trie[curr].endCnt > 0)
                return ans;

            // Try z -> a
            for(int i = 25; i >= 0; i--) {

                if(trie[curr].child[i] != -1) {
                    ans += char('a' + i);
                    curr = trie[curr].child[i];
                    break;
                }
            }
        }
    }

    // =========================================================
    // MOST FREQUENT WORD WITH PREFIX
    // =========================================================

    string maxFreq(string s) {
        int curr = 0;

        // Go to the prefix
        for(char c : s) {
            int x = c - 'a';

            if(trie[curr].child[x] == -1)
                return "";

            curr = trie[curr].child[x];
        }

        string ans = s;

        while(true) {

            // Frequency of the current word
            int bestFreq = trie[curr].endCnt;

            int bestChild = -1;

            // Find the child containing the most strings
            for(int i = 0; i < 26; i++) {

                int nxt = trie[curr].child[i];

                if(nxt == -1)
                    continue;

                if(trie[nxt].cnt > bestFreq) {
                    bestFreq = trie[nxt].cnt;
                    bestChild = i;
                }
            }

            // No child has a better answer
            if(bestChild == -1)
                return ans;

            ans += char('a' + bestChild);
            curr = trie[curr].child[bestChild];
        }
    }
};


// =============================================================
// SOLVE
// =============================================================

void solve() {

    int n;
    cin >> n;

    Trie trie;

    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;

        trie.insert(s);
    }

    int q;
    cin >> q;

    while(q--) {

        string s;
        cin >> s;

        cout << "Prefix: " << s << endl;

        cout << "Exists: "
             << trie.startsWith(s) << endl;

        cout << "Count: "
             << trie.countPrefix(s) << endl;

        cout << "Smallest: "
             << trie.findSmallest(s) << endl;

        cout << "Largest: "
             << trie.findLargest(s) << endl;

        cout << "Most frequent: "
             << trie.maxFreq(s) << endl;

        cout << endl;
    }
}


// =============================================================
// MAIN
// =============================================================

int32_t main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
