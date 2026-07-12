class Solution {
public:
    int m, n;
    vector<vector<vector<int>>> dp;
    vector<vector<bool>> vis;

    bool dfs(vector<vector<int>>& grid, int i, int j, int health) {

        // Out of bounds
        if (i < 0 || i >= m || j < 0 || j >= n)
            return false;

        // Already in current path
        if (vis[i][j])
            return false;

        // Pay the cost of current cell
        health -= grid[i][j];

        // Dead
        if (health <= 0)
            return false;

        // Reached destination
        if (i == m - 1 && j == n - 1)
            return true;

        // Memoized answer
        if (dp[i][j][health] != -1)
            return dp[i][j][health];

        vis[i][j] = true;

        bool ans =
            dfs(grid, i + 1, j, health) ||
            dfs(grid, i - 1, j, health) ||
            dfs(grid, i, j + 1, health) ||
            dfs(grid, i, j - 1, health);

        vis[i][j] = false;   // Backtrack

        return dp[i][j][health] = ans;
    }

    bool findSafeWalk(vector<vector<int>>& grid, int health) {

        m = grid.size();
        n = grid[0].size();

        dp.assign(m,
                  vector<vector<int>>(n,
                  vector<int>(health + 1, -1)));

        vis.assign(m, vector<bool>(n, false));

        return dfs(grid, 0, 0, health);
    }
};