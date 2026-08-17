#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

const int INF = 2e9;
const int ITERATIONS = 40; // Failure probability < (2/3)^40 ~ 9e-8

int n, q, k;
vector<int> a;
map<int, vector<int>> pos;

int get_freq(int val, int l, int r) {
    auto it = pos.find(val);
    if (it == pos.end()) return 0;
    const auto& vec = it->second;
    auto it_r = upper_bound(vec.begin(), vec.end(), r);
    auto it_l = lower_bound(vec.begin(), vec.end(), l);
    return static_cast<int>(it_r - it_l);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q >> k)) return 0;

    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        int ans = INF;
        int len = r - l + 1;

        for (int step = 0; step < ITERATIONS; step++) {
            int rand_idx = l + rng() % len;
            int cand = a[rand_idx];

            // Pruning optimization: Skip if candidate cannot improve minimum answer
            if (cand >= ans) continue;

            if (get_freq(cand, l, r) * k >= len) {
                ans = cand;
            }
        }

        if (ans == INF) cout << -1 << "\n";
        else cout << ans << "\n";
    }

    return 0;
}
