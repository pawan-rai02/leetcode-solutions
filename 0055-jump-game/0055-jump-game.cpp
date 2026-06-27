class Solution {
public:


    int n;
    int dp[10001];

    bool solve(vector<int>& nums, int i) {

        if (i >= n - 1)
            return dp[i] = true;

        if (nums[i] == 0)
            return dp[i] = false;
        
        if(dp[i] != -1)
            return dp[i];

        int maxJump = nums[i];

        for (int j = i + 1; j <= min(n - 1, i + maxJump); j++) {
            if (solve(nums, j))
                return dp[i] = true;
        }

        return dp[i] = false;

    }

    bool canJump(vector<int>& nums) {
        
        memset(dp, -1, sizeof(dp));

        n = nums.size();

        return solve(nums, 0);
    }
};