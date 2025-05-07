struct EulerTower {
	int n, timer = 1;
	vector <int> IN, OUT;
	vector <vector <int>> adj;
 
	EulerTower (int _n, const vector <vector <int>> &_adj, int root = 1): n(_n), adj(_adj), IN(n + 1), OUT(n + 1) {
		DFS(root, -1);
	}
 
	void DFS (int u, int p) {
		IN[u] = timer++;
		for (auto v : adj[u]) {
			if (v == p) continue;
	
			DFS(v, u);
		}
		OUT[u] = timer - 1;
	}
 
	int pos(int u) {
		return IN[u];
	}
 
	pair <int, int> subtree(int u) {
		return {IN[u], OUT[u]};
	}
};