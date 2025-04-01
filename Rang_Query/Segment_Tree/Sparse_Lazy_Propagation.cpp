struct Node {
    int left = -1;
    int right = -1;
    ll val;
    ll lazy;
    bool is_lazy;

    Node (ll _val = 0) {
        val = _val;
        reset();
    }

    void reset() {
        lazy = 0;
        is_lazy = 0;
    }

    void change(Node x) {
        val = x.val;
    }

    void change(ll x, int l, int r) {
        val += x * (r - l + 1);
        lazy += x;
        is_lazy = 1;
    }
};

struct SparseLazyPropagation {
#define mid ((l + r) / 2)

private:
    ll ln, timer = 1;
    vector <Node> seg;
    function <Node (const Node&, const Node&)> merge;

    void push_down(int node, int l, int r) {
        if (seg[node].left == -1) {
            seg[node].left = ++timer;
            seg.push_back(Node());
        }

        if (seg[node].right == -1) {
            seg[node].right = ++timer;
            seg.push_back(Node());
        }
    }

    void propagate(int node, int l, int r) {
        if (!seg[node].is_lazy or l == r) return;

        seg[seg[node].left].change(seg[node].lazy, l, mid);
        seg[seg[node].right].change(seg[node].lazy, mid + 1, r);

        seg[node].reset();
    }

    void update(int l, int r, int node, int idx, Node new_val) {
        if (l == r) {
            seg[node] = new_val;
            return;
        }

        push_down(node, l, r);

        if (idx <= mid) 
            update(l, mid, seg[node].left, idx, new_val);
        else
            update(mid + 1, r, seg[node].right, idx, new_val);

        seg[node].change(merge(seg[seg[node].left], seg[seg[node].right]));
    }

    void update(int l, int r, int node, int ql, int qr, ll new_val) {
        push_down(node, l, r);
        propagate(node, l, r);

        if (r < ql or l > qr) return;
        if (l >= ql and r <= qr) {
            seg[node].change(new_val, l, r);
            return;
        }

        update(l, mid, seg[node].left, ql, qr, new_val);
        update(mid + 1, r, seg[node].right, ql, qr, new_val);

        seg[node].change(merge(seg[seg[node].left], seg[seg[node].right]));
    }

    Node query(int l, int r, int node, int ql, int qr) {
        push_down(node, l, r);
        propagate(node, l, r);

        if (r < ql or l > qr) return Node();
        if (l >= ql and r <= qr) return seg[node];


        Node left = query(l, mid, seg[node].left, ql, qr);
        Node right = query(mid + 1, r, seg[node].right, ql, qr);

        return merge(left, right);
    }

public:
    SparseLazyPropagation (int n, const function <Node (const Node&, const Node&)> &op) {
        ln = n;
        merge = op;
        seg.resize(2);
    }

    void update(int l, int r, ll new_val) {
        update(1, ln, 1, l, r, new_val);
    }

    void update(int idx, Node new_val) {
        update(1, ln, 1, idx, new_val);
    }

    Node query(int l, int r) {
        return query(1, ln, 1, l, r);
    }

    Node query(int idx) {
        return query(1, ln, 1, idx, idx);
    }

#undef mid
};