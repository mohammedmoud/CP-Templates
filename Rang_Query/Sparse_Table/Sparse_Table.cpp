template <typename TP = ll>
struct SparseTable {
    int n;
    vector <TP> v;
    vector <vector <TP>> T;
    function <TP (TP, TP)> merge;
    vector <ll> LOG;
    TP SKIP;

    void init() {
        LOG = vector <ll> (n + 5, 0);
        for (int i = 2; i <= n; i++) {
            LOG[i] = LOG[i >> 1] + 1;
        } 
    }

    SparseTable(vector <TP> _v, function <TP (TP, TP)> _merge, TP _skip) {
        v = _v;
        n = len(v);
        SKIP = _skip;
        merge = _merge;
        T = vector <vector <TP>> (n + 5, vector <TP> (25, SKIP));
        build();
    }

    void build() {
        for (int i = 0; i < n; i++) {
            T[i][0] = v[i];
        }

        for (int pw = 1; (1 << pw) <= n; pw++) {
            for (int i = 0; i + (1 << pw) <= n; i++) {
                T[i][pw] = merge(T[i][pw - 1], T[i + (1 << (pw - 1))][pw - 1]);
            }
        }
    }

    TP fastQuery(int l, int r) {
        if (l > r) return SKIP;
        ll pw = LOG[r - l + 1];
        return merge(T[l][pw], T[r - (1 << pw) + 1][pw]);
    }

    TP query (int l, int r) {
        TP ret = SKIP;
        ll sz = r - l + 1;
        for (int pw = 23; pw >= 0; pw--) {
            if (isON(sz, pw)) {
                ret = merge(ret, T[l][pw]);
                l += (1 << pw);
            }
        }
        return ret;
    }
};
