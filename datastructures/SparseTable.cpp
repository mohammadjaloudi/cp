#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int LOG = 20;

int st[LOG][N];

void build(vector<int>& a) {

    int n = a.size();

    for (int i = 0; i < n; i++) {
        st[0][i] = a[i];
    }

    for (int k = 1; k < LOG; k++) {

        for (int i = 0; i + (1 << k) <= n; i++) {

            st[k][i] = min(
                st[k - 1][i],
                st[k - 1][i + (1 << (k - 1))]
            );
        }
    }
}

int query(int l, int r) {

    int len = r - l + 1;

    int k = __lg(len);

    return min(
        st[k][l],
        st[k][r - (1 << k) + 1]
    );
}

int main() {

    vector<int> a = {
        5, 2, 4, 7, 1, 3, 6, 8
    };

    build(a);

    cout << query(1, 6) << '\n';
}
