template <typename T = int>
struct LCA {
	const int LOG = 30;
	T SKIP;
	vector <vector <pair <int, T>>> adj;
	vector <vector <int>> up;
	vector <vector <T>> cost;
	vector <int> dep;
	function <T (T, T)> merge;

	LCA(int n, const vector <vector <pair <int, T>>> &_adj, const function <T (T, T)> &op, T _SK, int root = 1) {
		adj = _adj;
		merge = op;
		SKIP = _SK;
		dep.assign(n + 5, 0);
		up.assign(n + 5, vector <int> (LOG));
		cost.assign(n + 5, vector <T> (LOG, SKIP));
		build(root, 0);
	}

	void build(int u, int p) {
		for (auto &[v, w] : adj[u]) {
			if (v == p) continue;
			dep[v] = dep[u] + 1;
			up[v][0] = u, cost[v][0] = w;
			for (int i = 1; i < LOG; i++) {
				up[v][i] = up[up[v][i - 1]][i - 1];
				cost[v][i] = merge(cost[v][i - 1], cost[up[v][i - 1]][i - 1]);
			}
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
		if (dep[u] > dep[v]) swap(u, v);
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

	T get_cost(int u, int dis) {
		if (dep[u] < dis) return SKIP;
		T ret = SKIP;
		for (int i = 0; i < LOG; i++) {
			if (isON(dis, i)) {
				ret = merge(ret, cost[u][i]);
				u = up[u][i];
			}
		}
		return ret;
	}

	T query(int u, int v) {
		int LC = get_lca(u, v);
		return merge(get_cost(u, dep[u] - dep[LC]), get_cost(v, dep[v] - dep[LC]));
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

	// Check node k is in path between u and v
	bool on_path(int u, int v, int k) {
		int lca = get_lca(u, v);
		return ((get_lca(u, k) == k or get_lca(v, k) == k) and get_lca(k, lca) == lca);
	}
};