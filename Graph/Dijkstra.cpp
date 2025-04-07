template < typename T = int > struct Dijkstra {
	vector <vector <pair <int, T>>> adj;
	vector <T> dis, par;

	Dijkstra(int n, const vector <vector <pair <int, T>>> &_adj, int root = 1): adj(_adj), par(n + 1, -1), dis(n + 1, (T(OO) < 0 ? oo : OO)) {
		ShortestPath(root);
	}

	pair <T, int> front(set <pair <T, int>> &st) {
		return *st.begin();
	}
	
	void pop(set <pair <T, int>> &st) {
		st.erase(st.begin());
	}

	void ShortestPath(int src) {
		set <pair <T, int>> st;
		st.insert({0, src});
		dis[src] = 0;

		while (!st.empty()) {
			auto [cost, u] = front(st);
			pop(st);

			for (auto [v, w] : adj[u]) {
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					par[v] = u;
					st.insert({dis[v], v});
				}
			}
		}
	}

	vector <int> path (int v) {
		int u = v;
		vector <int> ret;
		ret.push_back(u);
		while (par[u] != -1) {
			u = par[u];
			ret.push_back(u);
		}
		reverse(all(ret));
		return ret;
	}

	T get_dis(int v) {
		return dis[v];
	}

	int get_par(int v) {
		return par[v];
	}
};