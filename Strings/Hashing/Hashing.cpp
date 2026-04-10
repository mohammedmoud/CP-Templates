struct Hash {
    ll BASE1 = 127, BASE2 = 131, MOD1 = 1e9 + 7, MOD2 = 998244353;
    ll H1 = 0, H2 = 0;
    deque < char > dq;

    Hash () {
        
    }

    Hash (string s) {
        for (char c : s) {
            push_back(c);
        }
    }

    ll power (ll a, ll b, ll m) {
        ll res = 1;
        while (b) {
            if (b & 1) res = mul(res, a, m);
            a = mul(a, a, m);
            b >>= 1;
        }
        return res;
    }

    ll add (ll a, ll b, ll m) {
        return ((a % m) + (b % m)) % m;
    }

    ll sub (ll a, ll b, ll m) {
        return ((a % m) - (b % m) + m) % m;
    }

    ll mul (ll a, ll b, ll m) {
        return ((a % m) * (b % m)) % m;
    }

    ll div (ll a, ll b, ll m) {
        return mul(a, power(b, m - 2, m), m);
    }

    ll fix(ll a, ll m) {
        return (a % m + m) % m;
    }

    void push_back(char c) {
        ll dg1 = fix(c + 1 - 'a', MOD1);
        ll dg2 = fix(c + 1 - 'a', MOD2);

        H1 = add(mul(H1, BASE1, MOD1), dg1, MOD1);
        H2 = add(mul(H2, BASE2, MOD2), dg2, MOD2);

        dq.push_back(c);
    }

    void pop_back() {
        if (dq.empty()) return;

        ll dg1 = fix(dq.back() + 1 - 'a', MOD1);
        ll dg2 = fix(dq.back() + 1 - 'a', MOD2);

        H1 = div(sub(H1, dg1, MOD1), BASE1, MOD1);
        H2 = div(sub(H2, dg2, MOD2), BASE2, MOD2);

        dq.pop_back();
    }
    
    void push_front(char c) {
        ll dg1 = fix(c + 1 - 'a', MOD1);
        ll dg2 = fix(c + 1 - 'a', MOD2);

        H1 = add(H1, mul(dg1, power(BASE1, len(dq), MOD1), MOD1), MOD1);
        H2 = add(H2, mul(dg2, power(BASE2, len(dq), MOD2), MOD2), MOD2);

        dq.push_front(c);
    }
    
    void pop_front() {
        if (dq.empty()) return;

        ll dg1 = fix(dq.front() + 1 - 'a', MOD1);
        ll dg2 = fix(dq.front() + 1 - 'a', MOD2);

        H1 = sub(H1, mul(dg1, power(BASE1, len(dq) - 1, MOD1), MOD1), MOD1);
        H2 = sub(H2, mul(dg2, power(BASE2, len(dq) - 1, MOD2), MOD2), MOD2);

        dq.pop_front();
    }

    string get_string() {
        string s;
        for (char c : dq) s += c;
        return s;
    }

    pair < ll, ll > get() {
        return {H1, H2};
    }
};