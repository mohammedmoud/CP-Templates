struct MergeSortTree {
private:
    int n;
    vector <vector <int>> seg;

    void build(int l, int r, int node, const vector <int> &v) {
        if (l == r) {
            seg[node].push_back(v[l]);
            return;
        }

        build(l, mid(l, r), leftNode(node), v);
        build(mid(l, r) + 1, r, rightNode(node), v);

        int i = 0, j = 0;
        while (i < len(seg[leftNode(node)]) and j < len(seg[rightNode(node)])) {
            if (seg[leftNode(node)][i] <= seg[rightNode(node)][j]) 
                seg[node].push_back(seg[leftNode(node)][i++]);
            else
                seg[node].push_back(seg[rightNode(node)][j++]);
        }

        while (i < len(seg[leftNode(node)])) seg[node].push_back(seg[leftNode(node)][i++]);
        while (j < len(seg[rightNode(node)])) seg[node].push_back(seg[rightNode(node)][j++]);
    }

    int bs(int node, ll val) {
        int l = 0, r = len(seg[node]) - 1, ans = len(seg[node]);
        while (l <= r) {
            int mid = (l + r) / 2;
            
            if (seg[node][mid] > val) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return len(seg[node]) - ans;
    }

    int query(int l, int r, int node, int ql, int qr, ll val) {
        if (r < ql or l > qr) return 0;
        if (l >= ql and r <= qr) return bs(node, val);

        int left = query(l, mid(l, r), leftNode(node), ql, qr, val);
        int right = query(mid(l, r) + 1, r, rightNode(node), ql, qr, val);

        return left + right;
    }

public:
    MergeSortTree(const vector <int> &v) {
        n = len(v) - 1;
        seg = vector <vector <int>> (4 * n);
        build(1, n, 1, v);
    }

    int query(int l, int r, ll val) {
        return query(1, n, 1, l, r, val);
    }

    int leftNode(int node) {
        return 2 * node;
    }

    int rightNode(int node) {
        return 2 * node + 1;
    }

    int mid (int l, int r) {
        return (l + r) / 2;
    }
    
    int parent(int node) {
        if (node == 1) return -1;
        return node / 2;
    }
};