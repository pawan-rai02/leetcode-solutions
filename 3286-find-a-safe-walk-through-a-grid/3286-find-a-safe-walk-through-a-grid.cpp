class Solution {
public:
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, 1, 0, -1};

    bool findSafeWalk(vector<vector<int>>& grid, int health) {

        int m = grid.size();
        int n = grid[0].size();

        deque<tuple<int, int, int>> dq;

        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

        dist[0][0] = grid[0][0];
        dq.push_back({grid[0][0], 0, 0});

        while (!dq.empty()) {

            auto [cost, i, j] = dq.front();
            dq.pop_front();

            // Skip outdated entries
            if (cost > dist[i][j])
                continue;

            if (i == m - 1 && j == n - 1)
                return cost < health;

            for (int k = 0; k < 4; k++) {
                int ni = i + dr[k];
                int nj = j + dc[k];

                if (ni < 0 || ni >= m || nj < 0 || nj >= n)
                    continue;

                int newCost = cost + grid[ni][nj];

                if (newCost >= dist[ni][nj])
                    continue;

                dist[ni][nj] = newCost;

                if (grid[ni][nj] == 0)
                    dq.push_front({newCost, ni, nj});
                else
                    dq.push_back({newCost, ni, nj});
            }
        }

        return false;
    }
};