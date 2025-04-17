struct LCA {
	const int LOG = 30;
	vector <vector <int>> adj, up;
	vector <int> dep;

	LCA(int n, const vector <vector <int>> &_adj, int root = 1) : dep(n + 5), adj(_adj) {
		up = vector <vector <int>> (n + 5, vector <int> (LOG));
		Build(root, 0);
	}

	void Build(int u, int p) {
		dep[u] = dep[p] + 1;
	
		up[u][0] = p;
		for (int i = 1; i < LOG; i++) {
			up[u][i] = up[up[u][i - 1]][i - 1];
		}
	
		for (auto v : adj[u]) {
			if (v == p) continue;
			Build(v, u);
		}
	}

	int KthAncestor(int u, int k) {
		if (k >= dep[u]) return -1;
		for (int i = 0; i < LOG; i++) {
			if (isON(k, i)) {
				u = up[u][i];
			}
		}
		return u;
	} 

	int Lca(int u, int v) {
		if (dep[v] < dep[u]) swap(u, v);
	
		v = KthAncestor(v, dep[v] - dep[u]);
	
		if (u == v) return u;
		
		for (int i = LOG - 1; i >= 0; i--) {
			if (up[u][i] != up[v][i]) {
				u = up[u][i];
				v = up[v][i];
			}
		}
		return up[u][0];
	}

	int Dis(int u, int v) {
		return dep[u] + dep[v] - 2 * dep[Lca(u, v)];
	}
};