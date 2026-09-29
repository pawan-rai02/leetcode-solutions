class Solution {
public:

    int dp[101][101][201];

    int m, n;

    bool solve(int i, int j, int oc, vector<vector<char>>& grid){

        oc += (grid[i][j] == '(') ? 1 : -1;

        if(oc < 0)
            return false;

        if(dp[i][j][oc] != -1)
            return dp[i][j][oc];

        if(i == m - 1 && j == n -1)
            return dp[i][j][oc] = oc == 0;

        if(i + 1 < m){
            if(solve(i + 1, j, oc, grid))
                return dp[i][j][oc] = true;
        }

        if(j + 1 < n){
            if(solve(i, j + 1, oc, grid))
                return dp[i][j][oc] = true;
        }

        return dp[i][j][oc] = false;
    }

    bool hasValidPath(vector<vector<char>>& grid) {

        n = grid[0].size();
        m = grid.size();

        memset(dp, -1, sizeof(dp));

        if((m + n - 1) % 2 == 1)
            return false;

        if(grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        return solve(0, 0, 0, grid);
        
    }
};