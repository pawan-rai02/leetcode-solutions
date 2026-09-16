class Solution {
public:

    int M = 1e9 + 7;
    int dp[1001][1001];

    int numberOfSets(int n, int K) {

        // Base case: k = 0
        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }

        for (int k = 1; k <= K; k++) {

            // suffix[i] = dp[k-1][i] + ... + dp[k-1][n-1]
            vector<int> suffix(n + 1, 0);

            for (int i = n - 1; i >= 0; i--) {
                suffix[i] = (suffix[i + 1] + dp[k - 1][i]) % M;
            }

            for (int i = n - 1; i >= 0; i--) {

                // dp[k-1][i+1] + ... + dp[k-1][n-1]
                int take = suffix[i + 1];

                // solve(k, i+1)
                int skip = (i + 1 < n) ? dp[k][i + 1] : 0;

                dp[k][i] = (take + skip) % M;
            }
        }

        return dp[K][0];
    }
};