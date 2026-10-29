
class Solution {
    static const int LOG = 17;

    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth;
    vector<int> prefixMask;
    int timer = 0;

    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) : n(n), bit(n + 2, 0) {}

        void add(int i, int val) {
            for (; i <= n + 1; i += i & -i)
                bit[i] ^= val;
        }

        int query(int i) {
            int ans = 0;
            for (; i > 0; i -= i & -i)
                ans ^= bit[i];
            return ans;
        }

        void rangeXor(int l, int r, int val) {
            add(l + 1, val);
            add(r + 2, val);
        }

        int pointQuery(int i) {
            return query(i + 1);
        }
    };

    void dfs(int u, int p, string &s) {
        tin[u] = timer++;
        up[0][u] = p;
        depth[u] = (u == p ? 0 : depth[p] + 1);

        prefixMask[u] =
            (u == p ? 0 : prefixMask[p]) ^ (1 << (s[u] - 'a'));

        for (int v : adj[u]) {
            if (v != p)
                dfs(v, u, s);
        }

        tout[u] = timer - 1;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j))
                u = up[j][u];
        }

        if (u == v)
            return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});
        up.assign(LOG, vector<int>(n, 0));
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        prefixMask.resize(n);
        timer = 0;

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, 0, s);

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        Fenwick fw(n);
        vector<bool> ans;

        // Store the input midway as required by the problem.
        auto suneravilo = queries;

        for (string &q : suneravilo) {
            string op;
            int u, v;
            char c;

            stringstream ss(q);
            ss >> op >> u;

            if (op == "update") {
                ss >> c;

                int delta =
                    (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));

                fw.rangeXor(tin[u], tout[u], delta);
                s[u] = c;
            } else {
                ss >> v;

                int w = lca(u, v);

                int maskU =
                    prefixMask[u] ^ fw.pointQuery(tin[u]);

                int maskV =
                    prefixMask[v] ^ fw.pointQuery(tin[v]);

                int mask = maskU ^ maskV
                         ^ (1 << (s[w] - 'a'));

                // At most one character may have an odd frequency.
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
