class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {

        int n = stones.size();

        vector<int> prefixSum(n);
        prefixSum[0] = stones[0];

        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + stones[i];
        }

        vector<int> dp(n);

        // Base case
        dp[n - 1] = prefixSum[n - 1];

        // Fill from right to left
        for (int i = n - 2; i >= 1; i--) {

            int take = prefixSum[i] - dp[i + 1];
            int skip = dp[i + 1];

            dp[i] = max(take, skip);
        }

        return dp[1];
    }
};