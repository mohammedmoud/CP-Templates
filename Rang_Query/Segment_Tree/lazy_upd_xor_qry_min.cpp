struct SegmentTree {
    int n;
    vector<ll> tree, lazy;

    SegmentTree(vector<ll>& a) {
        n = a.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(a, 1, 0, n - 1);
    }

    void build(vector<ll>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2*node, l, mid);
        build(a, 2*node+1, mid+1, r);
        tree[node] = min(tree[2*node], tree[2*node+1]);
    }

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            // Apply XOR
            tree[node] ^= lazy[node];
            if (l != r) {
                lazy[2*node] ^= lazy[node];
                lazy[2*node+1] ^= lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void range_xor(int node, int l, int r, int ql, int qr, int val) {
        push(node, l, r);
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            lazy[node] ^= val;
            push(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        range_xor(2*node, l, mid, ql, qr, val);
        range_xor(2*node+1, mid+1, r, ql, qr, val);
        tree[node] = min(tree[2*node], tree[2*node+1]);
    }

    ll range_min(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (qr < l || ql > r) return INT_MAX;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return min(
            range_min(2*node, l, mid, ql, qr),
            range_min(2*node+1, mid+1, r, ql, qr)
        );
    }

    void range_xor(int l, int r, int val) {
        range_xor(1, 0, n - 1, l, r, val);
    }

    int range_min(int l, int r) {
        return range_min(1, 0, n - 1, l, r);
    }
};