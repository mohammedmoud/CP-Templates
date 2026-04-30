struct num {
    ll v[6] = {};
 
    num () {
 
    }
 
    num (ll x) {
        for (int i = 0; i < 6; i++) {
            v[i] = rand(1, 1e9);
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
    friend ostream& operator << (ostream &out, const num &x) {
        for (int i = 0; i < 6; i++) {
            out << x.v[i];
            if (i < 5) out << " ";
        }
        return out;
    }
};