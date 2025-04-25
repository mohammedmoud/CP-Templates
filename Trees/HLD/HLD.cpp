struct HLD {
	vector <int> big, head, sz, dep, par, id;
	bool VAL_ON_EDGE;

	HLD (int n, const vector <vector <int>> &adj, bool _VAL_ON_EDGE = false): big(n + 5), head(n + 5), sz(n + 5), par(n + 5), id(n + 5), dep(n + 5) {
		VAL_ON_EDGE = _VAL_ON_EDGE;
		init(1, adj);
		head[1] = 1;
		int nxt = 1;
		build(1, adj, nxt);
	}

	void init(int u, const vector <vector <int>> &adj, int _ROOT = 1) {
		sz[u] = 1;
		for (auto v : adj[u]) {
			if (v == par[u]) continue;
			par[v] = u;
			dep[v] = dep[u] + 1;
			init(v, adj);
			sz[u] += sz[v];

			if (!big[u] or sz[v] > sz[big[u]]) big[u] = v;
		}
	}

	void build(int u, const vector <vector <int>> &adj, int &nxt) {
		id[u] = nxt++;

		if (big[u]) {
			head[big[u]] = head[u];
			build(big[u], adj, nxt);
		}

		for (auto v : adj[u]) {
			if (v == par[u] or v == big[u]) continue;
			head[v] = v;
			build(v, adj, nxt);
		}
	}

	pair <int, int> subTree(int u) {
		return {id[u], id[u] + sz[u] - 1};
	}

	int getChild(int u, int v) {
		if (par[u] == v) return u;
		return v;
	}

	void makeULower(int &u, int &v) {
		if (dep[head[u]] > dep[head[v]] or (head[u] == head[v] and dep[u] > dep[v]))
			swap(u, v);
	}

	pair <int, int> moveUp(int &v) {
		pair <int, int> ret = {id[head[v]], id[v]};
		v = par[head[v]];
		return ret;
	}

	vector <pair <int, int>> query(int u, int v) {
		vector <pair <int, int>> ret;
		while (head[u] != head[v]) {
			makeULower(u, v);
			ret.push_back(moveUp(v));
		}
		makeULower(u, v);
		if (!VAL_ON_EDGE)
			ret.push_back({id[u], id[v]});
		else if (u != v)
			ret.push_back({id[u] + 1, id[v]});
		return ret;
	}
};