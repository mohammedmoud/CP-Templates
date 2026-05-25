struct Trie {
    struct Node {
        Node *CH[26];
        int PRE, END;

        Node () {
            PRE = END = 0;
            memset(CH, 0, sizeof CH);
        }
    };

    Node *root = new Node();

    int pos(const char &c) {
        return c - 'a';
    }

    void insert (const string &s) {
        Node *cur = root;
        for (auto &c : s) {
            int idx = pos(c);
            if (cur->CH[idx] == 0) {
                cur->CH[idx] = new Node();
            }
            cur = cur->CH[idx];
            cur->PRE += 1;
        }
        cur->END += 1;
    }

    int count (const string &s) {
        Node *cur = root;
        for (auto &c : s) {
            int idx = pos(c);
            if (cur->CH[idx] == 0) {
                return 0;
            }
            cur = cur->CH[idx];
        }
        return cur->PRE;
    }

    void remove(const string &s) {
        remove(s, 0, root);
    }

    void remove(const string &s, int i, Node *cur) {
        if (i >= len(s)) return;
        int idx = pos(s[i]);
        if (cur -> CH[idx]) {
            remove(s, i + 1, cur -> CH[idx]);
            cur -> CH[idx] -> PRE -= 1;
            if (i == len(s) - 1) {
                cur -> CH[idx] -> END -= 1;
            }

            if (cur -> CH[idx] -> PRE == 0) {
                delete cur -> CH[idx];
                cur -> CH[idx] = 0;
            }
        }
    }
};