struct LCA {
	const int LOG = 30;
	vector <vector <int>> adj, up;
	vector <int> dep;

	LCA(int n, const vector <vector <int>> &_adj, int root = 1) : dep(n + 5), adj(_adj) {
		up = vector <vector <int>> (n + 5, vector <int> (LOG));
		build(root, 0);
	}

	void build(int u, int p) {
		up[u][0] = p;
		for (int i = 1; i < LOG; i++) {
			up[u][i] = up[up[u][i - 1]][i - 1];
		}

		for (auto v : adj[u]) {
			if (v == p) continue;
			dep[v] = dep[u] + 1;
			build(v, u);
		}
	}

	int kth_ancestor(int u, int k) {
		if (k > dep[u]) return -1;
		for (int i = 0; i < LOG; i++) {
			if (isON(k, i)) {
				u = up[u][i];
			}
		}
		return u;
	} 

	int get_lca(int u, int v) {
		if (dep[v] < dep[u]) swap(u, v);

		v = kth_ancestor(v, dep[v] - dep[u]);

		if (u == v) return u;

		for (int i = LOG - 1; i >= 0; i--) {
			if (up[u][i] != up[v][i]) {
				u = up[u][i];
				v = up[v][i];
			}
		}
		return up[u][0];
	}

	int get_dis(int u, int v) {
		return dep[u] + dep[v] - 2 * dep[get_lca(u, v)];
	}

	// Node i for the path fromt s to t
	int idx_path(int s, int t, int i) {
		int ln = get_dis(s, t);
		if (i > ln) {
			return -1;
		}

		int lc = get_lca(s, t);
		if (i <= dep[s] - dep[lc]) {
			return kth_ancestor(s, i);			
		} else {
			return kth_ancestor(t, ln - i);			
		}
	}

	// Check node k is in path from u to v
	bool on_path(int u, int v, int k) {
		int lca = get_lca(u, v);
		return ((get_lca(u, k) == k or get_lca(v, k) == k) and get_lca(k, lca) == lca);
	}
};