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

    int kthAncestor(int u, int k) {
        if (k > dep[u]) return -1;
        for (int i = 0; i < LOG; i++) {
            if (isON(k, i)) {
                u = up[u][i];
            }
        }
        return u;
    }

    int getLca(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        v = kthAncestor(v, dep[v] - dep[u]);

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    T getCost(int u, int dis) {
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
        int LC = getLca(u, v);
        return merge(getCost(u, dep[u] - dep[LC]), getCost(v, dep[v] - dep[LC]));
    }
};