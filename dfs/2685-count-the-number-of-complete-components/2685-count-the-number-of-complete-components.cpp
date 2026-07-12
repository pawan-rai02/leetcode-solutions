class Solution {
public:

    void dfs(unordered_map<int, vector<int>>& adj,
             int u,
             vector<bool>& vis,
             int &nodes,
             int &edges){

        vis[u] = true;
        nodes++;

        edges += adj[u].size();

        for(int v : adj[u]){
            if(!vis[v]){
                dfs(adj, v, vis, nodes, edges);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        unordered_map<int, vector<int>> adj;

        for(auto &e : edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> vis(n,false);

        int ans = 0;

        for(int i=0;i<n;i++){

            if(!vis[i]){

                int nodes = 0;
                int edgeCount = 0;

                dfs(adj,i,vis,nodes,edgeCount);

                edgeCount /= 2;

                if(edgeCount == nodes*(nodes-1)/2)
                    ans++;
            }
        }

        return ans;
    }
};