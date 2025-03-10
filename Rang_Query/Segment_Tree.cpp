struct SegmentTree {
private:
#define leftNode 2 * node
#define rightNode 2 * node + 1
#define mid (l + r) / 2

    ll ln, skip;
    vector <ll> seg;
    function <ll(ll, ll)> merge;

    void update(int l, int r, int node, int idx, ll new_val) {
        if (l == r) {
            seg[node] = new_val;
            return;
        }

        if (idx <= mid)
            update(l, mid, leftNode, idx, new_val);
        else
            update(mid + 1, r, rightNode, idx, new_val);

        seg[node] = merge(seg[leftNode], seg[rightNode]);
    }

    ll query(int l, int r, int node, int ql, int qr) {
        if (l > qr or r < ql) return skip;
        if (l >= ql and r <= qr) return seg[node];

        ll left = query(l, mid, leftNode, ql, qr);
        ll right = query(mid + 1, r, rightNode, ql, qr);

        return merge(left, right);
    }

public:
    SegmentTree(int n, function <ll(ll, ll)> op, int _skip) {
        ln = n;
        skip = _skip;
        merge = op;
        seg.resize(4 * ln, skip);
    }

    void update(int idx, ll new_val) {
        update(1, ln, 1, idx, new_val);
    }
    
    ll query(int l, int r) {
        return query(1, ln, 1, l, r);
    }

#undef leftNode
#undef rightNode
#undef mid
};