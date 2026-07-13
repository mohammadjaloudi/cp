struct SumSegTree {
    using T = long long;              
    static constexpr T ID = 0;
    int n = 0;
    int base = 1;
    vector<T> tree;

    SumSegTree() {}

    SumSegTree(const vector<T>& a) {
        init(a);
    }

    static T merge_values(T left_value, T right_value) {
        return left_value + right_value;
    }

    void init(const vector<T>& a) {
        n = (int)a.size();

        base = 1;
        while (base < max(1, n)) {
            base <<= 1;
        }

        tree.assign(2 * base, ID);

        build(0, 0, base - 1, a);
    }

    void build(int i, int l, int r, const vector<T>& a) {
        if (l == r) {
            if (l < n) {
                tree[i] = a[l];
            } else {
                tree[i] = ID;
            }
            return;
        }

        int left = 2 * i + 1;
        int right = left + 1;
        int mid = l + (r - l) / 2;

        build(left, l, mid, a);
        build(right, mid + 1, r, a);

        tree[i] = merge_values(tree[left], tree[right]);
    }

    void point_set(int pos, T value) {
        point_set(pos, value, 0, 0, base - 1);
    }

    void point_set(int pos, T value, int i, int l, int r) {
        if (pos < l || r < pos) {
            return;
        }

        if (l == r) {
            tree[i] = value;
            return;
        }

        int left = 2 * i + 1;
        int right = left + 1;
        int mid = l + (r - l) / 2;

        point_set(pos, value, left, l, mid);
        point_set(pos, value, right, mid + 1, r);

        tree[i] = merge_values(tree[left], tree[right]);
    }

    T query(int ql, int qr) const {
        return query(ql, qr, 0, 0, base - 1);
    }

    T query(int ql, int qr, int i, int l, int r) const {
        if (qr < l || r < ql) {
            return ID;
        }

        if (ql <= l && r <= qr) {
            return tree[i];
        }

        int left = 2 * i + 1;
        int right = left + 1;
        int mid = l + (r - l) / 2;

        T left_answer = query(ql, qr, left, l, mid);
        T right_answer = query(ql, qr, right, mid + 1, r);

        return merge_values(left_answer, right_answer);
    }
};
