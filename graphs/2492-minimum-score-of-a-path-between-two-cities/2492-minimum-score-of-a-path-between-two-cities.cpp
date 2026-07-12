class Solution {
public:
    void dfs(vector<vector<pair<int, int>>> &adj,
             vector<bool> &vis,
             int src,
             int &res)
    {
        vis[src] = true;

        for (auto &p : adj[src]) {
            int v = p.first;
            int wt = p.second;

            res = min(res, wt);

            if (!vis[v]) {
                dfs(adj, vis, v, res);
            }
        }
    }

    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> adj(n + 1);

        // Build the undirected graph
        for (auto &road : roads) {
            int u = road[0];
            int v = road[1];
            int wt = road[2];

            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        vector<bool> vis(n + 1, false);
        int res = INT_MAX;

        dfs(adj, vis, 1, res);

        return res;
    }
};