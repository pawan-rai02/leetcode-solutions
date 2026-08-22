class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        
        vector<vector<int>> adj(n);

        vector<int> inDegree(n, 0);
        vector<bool> sus(n, false);

        for(auto &edge : invocations){
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);

            inDegree[v]++;
        }

        //bfs
        queue<int> que;
        que.push(k);
        sus[k] = true;

        while(!que.empty()){

            int curr = que.front();
            que.pop();

            for(int &ngbr : adj[curr]){
                inDegree[ngbr]--;

                if(!sus[ngbr]){
                    que.push(ngbr);
                    sus[ngbr] = true;
                }
            }
        }

        vector<int> res;
        bool cant_remove = false;

        for(int i = 0; i < n; i++){
            if(sus[i] && inDegree[i] > 0){
                cant_remove = true;
                break;
            }

            if(!sus[i])
                res.push_back(i);
        }

        if(cant_remove){
            vector<int> vec(n);
            for(int i = 0; i < n; i++)
                vec[i] = i;

            return vec;
        }

        return res;
    }
};