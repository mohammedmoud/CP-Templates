struct Node {
	ll mn, cnt;
	Node (ll _mn = oo, ll _cnt = 0) {mn = _mn, cnt = _cnt;}
};

struct SegmentTree {
#define leftNode 2 * node
#define rightNode 2 * node + 1
#define mid (l + r) / 2

private:
	ll ln;
	vector <Node> seg;
	function <Node (const Node&, const Node&)> merge;

	void update(int l, int r, int node, int idx, Node new_val) {
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

	Node query(int l, int r, int node, int ql, int qr) {
		if (l > qr or r < ql) return Node();
		if (l >= ql and r <= qr) return seg[node];

		Node left = query(l, mid, leftNode, ql, qr);
		Node right = query(mid + 1, r, rightNode, ql, qr);

		return merge(left, right);
	}

public:
	SegmentTree(int n, const function <Node (const Node&, const Node&)> &op) {
		ln = n;
		merge = op;
		seg.resize(4 * ln);
	}

	void update(int idx, Node new_val) {
		update(1, ln, 1, idx, new_val);
	}
	
	Node query(int l, int r) {
		return query(1, ln, 1, l, r);
	}

#undef leftNode
#undef rightNode
#undef mid
};