ll BASE1 = 127, BASE2 = 131, MOD1 = 1e9 + 7, MOD2 = 998244353;
vector <ll> pw1, pw2, inv1, inv2;

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
    pw1[0] = pw2[0] = inv1[0] = inv2[0] = 1;

    ll temp1 = power(BASE1, MOD1 - 2, MOD1);
    ll temp2 = power(BASE2, MOD2 - 2, MOD2);

    for (int i = 1; i <= ln; i++) {
        pw1[i] = mul(pw1[i - 1], BASE1, MOD1);
        pw2[i] = mul(pw2[i - 1], BASE2, MOD2);

        inv1[i] = mul(inv1[i - 1], temp1, MOD1);
        inv2[i] = mul(inv2[i - 1], temp2, MOD2);
    }
}

struct Node {
    ll sz;
    ll H1, H2;
	Node (ll _sz = 0, ll _H1 = 0, ll _H2 = 0) {sz = _sz, H1 = _H1, H2 = _H2;}
    bool operator == (const Node &other) const {
        return H1 == other.H1 and H2 == other.H2 and sz == other.sz;
    }
    bool operator < (const Node &other) const {
        if (H1 != other.H1) return H1 < other.H1;
        if (H2 != other.H2) return H2 < other.H2;
        return sz < other.sz;
    }
};

struct HashingSegmentTree {
#define leftNode 2 * node
#define rightNode 2 * node + 1
#define mid (l + r) / 2

private:
    ll ln;
    vector <Node> seg;

	void update(int l, int r, int node, int idx, ll ch) {
		if (l == r) {
			seg[node] = Node (
                1, 
                mul(fix(ch, MOD1), pw1[ln - idx], MOD1), 
                mul(fix(ch, MOD2), pw2[ln - idx], MOD2)
            );
			return;
		}

		if (idx <= mid)
			update(l, mid, leftNode, idx, ch);
		else
			update(mid + 1, r, rightNode, idx, ch);

		seg[node] = merge(seg[leftNode], seg[rightNode]);
	}

	Node query(int l, int r, int node, int ql, int qr) {
		if (l > qr or r < ql) return Node();
		if (l >= ql and r <= qr) return seg[node];

		Node left = query(l, mid, leftNode, ql, qr);
		Node right = query(mid + 1, r, rightNode, ql, qr);

		return merge(left, right);
	}

    Node merge(const Node &left, const Node &right) {
        Node res;
        res.H1 = add(left.H1, right.H1, MOD1);
        res.H2 = add(left.H2, right.H2, MOD2);
        res.sz = left.sz + right.sz;
        return res;
    }

public:
	HashingSegmentTree(int n) {
		ln = n;
		seg.resize(4 * (ln + 1), Node());
	}

	void update(int idx, char ch) {
		update(1, ln, 1, idx, ch - 'a' + 1);
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