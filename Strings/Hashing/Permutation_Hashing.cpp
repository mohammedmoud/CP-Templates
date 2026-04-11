struct num {
    ll v[6] = {};
 
    num () {
 
    }
 
    num (ll x) {
        for (int i = 0; i < 6; i++) {
            v[i] = rand(1, 1e12);
        }
    }
 
    bool operator < (const num &other) const {
        for (int i = 0; i < 6; i++) {
            if (v[i] != other.v[i]) {
                return v[i] < other.v[i];
            }
        }
        return false;
    }
 
    bool operator == (const num &other) const {
        for (int i = 0; i < 6; i++) {
            if (v[i] != other.v[i]) {
                return false;
            }
        }
        return true;
    }
 
    num operator + (const num &other) const {
        num result;
        for (int i = 0; i < 6; i++) {
            result.v[i] = v[i] + other.v[i];
        }
        return result;
    }
    num operator - (const num &other) const {
        num result;
        for (int i = 0; i < 6; i++) {
            result.v[i] = v[i] - other.v[i];
        }
        return result;
    }
};
 
signed main() {
    MO();
 
    int t;
    cin >> t;
 
    while (t--) {
        int n, q;
        cin >> n >> q;
 
        map <ll, num> mp;
        vector <num> pre(n + 3);
        for (int i = 1; i <= n; i++) {
            ll x;
            cin >> x;
 
            if (mp.find(x) == mp.end()) {
                mp[x] = num(x);
            }
 
            pre[i] = (pre[i - 1] + mp[x]);
        }
 
        while (q--) {
            int l, r;
            cin >> l >> r;
 
            cout << yes((pre[r] - pre[l - 1]) == num()) << endl;
        }
    }
 
    return 0;
}
