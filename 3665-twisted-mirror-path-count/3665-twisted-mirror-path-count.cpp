class Solution {
public:
    int M = 1e9 + 7;
    int n, m;

    int solve(int i, int j, int dir, vector<vector<int>>& grid, vector<vector<vector<int>>>& dp){

        if(i >= n || j >= m)
            return 0;

        if(i == n-1 && j == m-1)
            return 1;

        if(dp[i][j][dir] != -1)
            return dp[i][j][dir];

        long long ways = 0;

        if(grid[i][j] == 1){
            // mirror 
            if(dir == 0) // coming from left (moving right)
                ways = solve(i+1, j, 1, grid, dp); // go down
            else // coming from top (moving down)
                ways = solve(i, j+1, 0, grid, dp); // go right
        }
        else{
            // normal both options
            ways += solve(i+1, j, 1, grid, dp);
            ways += solve(i, j+1, 0, grid, dp);
        }

        return dp[i][j][dir] = ways % M;
    }

    int uniquePaths(vector<vector<int>>& grid) {

        n = grid.size();
        m = grid[0].size();

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(2, -1)));

        return solve(0, 0, 0, grid, dp) % M;
    }
};