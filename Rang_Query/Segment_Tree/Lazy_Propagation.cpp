struct Node {
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

	void change(ll x, int l, int r) {
		val = x * (r - l + 1);
		lazy = x;
		is_lazy = 1;
	}
};

struct LazyPropagation {
#define leftNode 2 * node
#define rightNode 2 * node + 1
#define mid ((l + r) / 2)

private:
	ll ln;
	vector <Node> seg;
	function <Node (const Node&, const Node&)> merge;

	void propagate(int node, int l, int r) {
		if (!seg[node].is_lazy or l == r) return;

		seg[leftNode].change(seg[node].lazy, l, mid);
		seg[rightNode].change(seg[node].lazy, mid + 1, r);

		seg[node].reset();
	}

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

	void update(int l, int r, int node, int ql, int qr, ll new_val) {
		propagate(node, l, r);

		if (r < ql or l > qr) return;
		if (l >= ql and r <= qr) {
			seg[node].change(new_val, l, r);
			return;
		}

		update(l, mid, leftNode, ql, qr, new_val);
		update(mid + 1, r, rightNode, ql, qr, new_val);

		seg[node] = merge(seg[leftNode], seg[rightNode]);
	}

	Node query(int l, int r, int node, int ql, int qr) {
		propagate(node, l, r);

		if (r < ql or l > qr) return Node();
		if (l >= ql and r <= qr) return seg[node];

		Node left = query(l, mid, leftNode, ql, qr);
		Node right = query(mid + 1, r, rightNode, ql, qr);

		return merge(left, right);
	}

public:
	LazyPropagation (int n, const function <Node (const Node&, const Node&)> &op) {
		ln = n;
		merge = op;
		seg.resize(4 * ln);
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

#undef leftNode
#undef rightNode
#undef mid
};