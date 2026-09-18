#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1'000'000'007;

mt19937 rng(
    chrono::steady_clock::now().time_since_epoch().count()
);

const ll P =
    uniform_int_distribution<ll>(256, MOD - 2)(rng);

struct Hash {
    int n;
    vector<ll> prefix;
    vector<ll> power;

    Hash(const string &s) {
        n = s.size();

        prefix.assign(n + 1, 0);
        power.assign(n + 1, 1);

        // P^i
        for(int i = 1; i <= n; i++) {
            power[i] = power[i - 1] * P % MOD;
        }

        // Prefix hashes
        for(int i = 0; i < n; i++) {
            ll val = s[i] - 'a' + 1;

            prefix[i + 1] =
                (prefix[i] * P + val) % MOD;
        }
    }

    // hash of s[l ... r], inclusive
    ll getHash(int l, int r) {
        int len = r - l + 1;

        return (
            prefix[r + 1]
            - prefix[l] * power[len] % MOD
            + MOD
        ) % MOD;
    }
};

void solve() {
    string s, t;
    cin >> s >> t;

    int n = s.size();
    int m = t.size();

    if(m > n) {
        cout << 0 << '\n';
        return;
    }

    Hash hs(s);
    Hash ht(t);

    ll target = ht.getHash(0, m - 1);

    int ans = 0;

    for(int i = 0; i + m <= n; i++) {
        if(hs.getHash(i, i + m - 1) == target) {
            ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
