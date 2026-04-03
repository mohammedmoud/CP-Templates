class HLD {
private:
    vector<vector<int> > adj;
    vector<int> dep, par, root, pos, cnt, heavy;
    int cur_pos;
    bool on_Edges;
 
public:
    HLD(int n, vector<vector<int> > &Graph, int TRoot = 1, bool onEdg = 0) {
        cur_pos = 1;
        on_Edges = onEdg;
        adj = Graph;
        dep = par = root = pos = cnt = heavy = vector<int>(n + 5);
        init(TRoot);
        build(TRoot);
    }
 
    void init(int v, int p = -1, int d = 0) {
        dep[v] = d, par[v] = p, cnt[v] = 1;
        for (int u: adj[v]) {
            if (u != p) {
                init(u, v, d + 1);
                cnt[v] += cnt[u];
                if (cnt[u] > cnt[heavy[v]])
                    heavy[v] = u;
            }
        }
    }
 
    void build(int v, bool newChain = true) {
        root[v] = newChain ? v : root[par[v]];
        pos[v] = cur_pos++;
        if (heavy[v])
            build(heavy[v], false);
        for (int u: adj[v]) {
            if (u != par[v] && u != heavy[v])
                build(u, true);
        }
    }
 
    vector<pair<int, int> > query(int u, int v, bool order = false) {
        vector<pair<int, int> > ans, up, down;
        while (root[u] != root[v]) {
            if (dep[root[u]] >= dep[root[v]]) {
                if (order)
                    up.push_back({pos[u], pos[root[u]]});
                else
                    ans.push_back({pos[root[u]], pos[u]});
                u = par[root[u]];
            } else {
                if (order)
                    down.push_back({pos[root[v]], pos[v]});
                else
                    ans.push_back({pos[root[v]], pos[v]});
                v = par[root[v]];
            }
        }
 
        if (order) {
            if (!on_Edges) {
                if (dep[u] >= dep[v])
                    up.push_back({pos[u], pos[v]});
                else
                    down.push_back({pos[u], pos[v]});
            } else if (u != v) {
                if (dep[u] >= dep[v])
                    up.push_back({pos[u] + 1, pos[v]});
                else
                    down.push_back({pos[u] + 1, pos[v]});
            }
 
            for (auto &p: up) ans.push_back(p);
            for (int i = (int) down.size() - 1; i >= 0; --i)
                ans.push_back(down[i]);
        } else {
            if (make_pair(dep[root[u]], dep[u]) < make_pair(dep[root[v]], dep[v]))
                swap(u, v);
            if (!on_Edges)
                ans.push_back({pos[v], pos[u]});
            else if (u != v)
                ans.push_back({pos[v] + 1, pos[u]});
        }
 
        return ans;
    }
 
    int get_edge_pos(int u, int v) {
        if (par[u] == v)
            return pos[u];
        return pos[v];
    }
 
    int get_pos(int u) {
        return pos[u];
    }
 
    int get_cnt(int u) {
        return cnt[u];
    }
};