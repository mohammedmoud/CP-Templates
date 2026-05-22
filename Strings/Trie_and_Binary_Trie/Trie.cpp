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
};