class Solution {
public:
    int m, n;
    vector<vector<int>> dp;

    int dfs(vector<vector<int>>& mat, int i, int j) {

        if (dp[i][j] != -1)
            return dp[i][j];

        int up = 0, down = 0, left = 0, right = 0;

        if (i + 1 < m && mat[i + 1][j] > mat[i][j])
            down = dfs(mat, i + 1, j);

        if (i - 1 >= 0 && mat[i - 1][j] > mat[i][j])
            up = dfs(mat, i - 1, j);

        if (j + 1 < n && mat[i][j + 1] > mat[i][j])
            right = dfs(mat, i, j + 1);

        if (j - 1 >= 0 && mat[i][j - 1] > mat[i][j])
            left = dfs(mat, i, j - 1);

        return dp[i][j] = 1 + max({up, down, left, right});
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {

        m = matrix.size();
        n = matrix[0].size();

        dp.assign(m, vector<int>(n, -1));

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, dfs(matrix, i, j));
            }
        }

        return ans;
    }
};