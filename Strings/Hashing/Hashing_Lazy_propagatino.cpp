ll BASE1 = 127, BASE2 = 131, MOD1 = 1e9 + 7, MOD2 = 998244353;
vector <ll> pw1, pw2, inv1, inv2, pre1, pre2;

ll add(ll a, ll b, ll mod) {
    return ((a % mod) + (b % mod)) % mod;
}

ll mul(ll a, ll b, ll mod) {
    return ((a % mod) * (b % mod)) % mod;
}

ll sub(ll a, ll b, ll mod) {
    return ((a % mod) - (b % mod) + mod) % mod;
}

ll power(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

ll div(ll a, ll b, ll mod) {
    return mul(a, power(b, mod - 2, mod), mod);
}

ll fix(ll a, ll m) {
    return ((a % m) + m) % m;
}

void init(int ln) {
    pw1.resize(ln + 1), pw2.resize(ln + 1), inv1.resize(ln + 1), inv2.resize(ln + 1);
    pre1.resize(ln + 1), pre2.resize(ln + 1);
    pw1[0] = pw2[0] = inv1[0] = inv2[0] = 1;
    pre1[0] = pre2[0] = 1;
    
    ll temp1 = power(BASE1, MOD1 - 2, MOD1);
    ll temp2 = power(BASE2, MOD2 - 2, MOD2);
    
    for (int i = 1; i <= ln; i++) {
        pw1[i] = mul(pw1[i - 1], BASE1, MOD1);
        pw2[i] = mul(pw2[i - 1], BASE2, MOD2);

        pre1[i] = add(pre1[i - 1], pw1[i], MOD1);
        pre2[i] = add(pre2[i - 1], pw2[i], MOD2);

        inv1[i] = mul(inv1[i - 1], temp1, MOD1);
        inv2[i] = mul(inv2[i - 1], temp2, MOD2);
    }
}

struct Node {
	ll H1, H2;
    ll sz;
	ll lazy;
	bool is_lazy;

	Node (ll _H1 = 0, ll _H2 = 0, ll _sz = 0) {
		H1 = _H1;
		H2 = _H2;
		sz = _sz;
		reset();
	}

	void reset() {
		lazy = 0;
		is_lazy = 0;
	}

    ll query_pw(int l, int r, int n, int which) {
        ll m = (which == MOD1) ? MOD1 : MOD2;
        return sub((which == MOD1) ? pre1[n - l] : pre2[n - l], (n - r - 1 >= 0 ? (which == MOD1 ? pre1[n - r - 1] : pre2[n - r - 1]) : 0), m);
    }

	void change(ll x, int l, int r, int n) {
		H1 = mul(x, query_pw(l, r, n, MOD1), MOD1);
		H2 = mul(x, query_pw(l, r, n, MOD2), MOD2);
        sz = r - l + 1;
		lazy = x;
		is_lazy = 1;
	}

    bool operator == (const Node &other) const {
        return H1 == other.H1 and H2 == other.H2 and sz == other.sz;
    }
};

struct HashingLazyPropagation {
#define leftNode 2 * node
#define rightNode 2 * node + 1
#define mid ((l + r) / 2)

private:
	ll ln;
	vector <Node> seg;
	// function <Node (const Node&, const Node&)> merge;

    Node merge (const Node &a, const Node &b) {
        Node res;
        res.H1 = add(a.H1, b.H1, MOD1);
        res.H2 = add(a.H2, b.H2, MOD2);
        res.sz = a.sz + b.sz;
        return res;
    }

	void propagate(int node, int l, int r) {
		if (!seg[node].is_lazy or l == r) return;

		seg[leftNode].change(seg[node].lazy, l, mid, ln);
		seg[rightNode].change(seg[node].lazy, mid + 1, r, ln);

		seg[node].reset();
	}

	void update(int l, int r, int node, int ql, int qr, ll new_val) {
		propagate(node, l, r);

		if (r < ql or l > qr) return;
		if (l >= ql and r <= qr) {
			seg[node].change(new_val, l, r, ln);
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
	HashingLazyPropagation (int n) {
		ln = n;
		seg.resize(4 * (ln + 1));
	}

	void update(int l, int r, char c) {
		update(1, ln, 1, l, r, c - 'a' + 1);
	}

	Node query(int l, int r) {
		Node res = query(1, ln, 1, l, r);
        res.H1 = mul(res.H1, inv1[ln - r], MOD1);
        res.H2 = mul(res.H2, inv2[ln - r], MOD2);
		return res;
	}

#undef leftNode
#undef rightNode
#undef mid
};

Node merge(const Node &left, const Node &right) {
    Node res;
    res.H1 = add(mul(left.H1, pw1[right.sz], MOD1), right.H1, MOD1);
    res.H2 = add(mul(left.H2, pw2[right.sz], MOD2), right.H2, MOD2);
    res.sz = left.sz + right.sz;
    return res;
}