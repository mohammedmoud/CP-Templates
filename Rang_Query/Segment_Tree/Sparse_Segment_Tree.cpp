struct Node {
	ll val;
	int left = -1;
	int right = -1;
	Node (ll _val = 0) {val = _val;}

	void change(Node oth) {
		val = oth.val;
	}
};

struct SparseSegmentTree {
#define mid (l + (r - l) / 2)

private:
	ll ln;
	int timer = 1;
	vector <Node> seg;
	function <Node (const Node&, const Node&)> merge;

	void push_down(int l, int r, int node) {
		if (seg[node].left == -1) {
			seg[node].left = ++timer;
			seg.push_back(Node());
		}

		if (seg[node].right == -1) {
			seg[node].right = ++timer;
			seg.push_back(Node());
		} 
	}

	void update(int l, int r, int node, int idx, Node new_val) {
		if (l == r) {
			seg[node] = new_val;
			return;
		}
		
		push_down(l, r, node);

		if (idx <= mid)
			update(l, mid, seg[node].left, idx, new_val);
		else
			update(mid + 1, r, seg[node].right, idx, new_val);

		seg[node].change(merge(seg[seg[node].left], seg[seg[node].right]));
	}

	Node query(int l, int r, int node, int ql, int qr) {
		if (l > qr or r < ql) return Node();
		if (l >= ql and r <= qr) return seg[node];
		
		push_down(l, r, node);

		Node left = query(l, mid, seg[node].left, ql, qr);
		Node right = query(mid + 1, r, seg[node].right, ql, qr);

		return merge(left, right);
	}

public:
	SparseSegmentTree(int n, int q, const function <Node (const Node&, const Node&)> &op) {
		ln = n;
		merge = op;
		seg.resize(2);
	}

	void update(int idx, Node new_val) {
		update(1, ln, 1, idx, new_val);
	}

	Node query(int l, int r) {
		return query(1, ln, 1, l, r);
	}

#undef mid
};