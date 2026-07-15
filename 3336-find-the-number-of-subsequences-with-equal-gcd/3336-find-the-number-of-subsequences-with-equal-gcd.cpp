class Solution {
public:
    static const int MOD = 1e9 + 7;

    long long dp[201][201][201];

    long long solve(vector<int>& nums, int i, int first, int second) {

        if (i == nums.size()) {
            bool nonEmpty = (first != 0 && second != 0);
            bool gcdMatch = (first == second);

            return (nonEmpty && gcdMatch) ? 1 : 0;
        }

        if (dp[i][first][second] != -1)
            return dp[i][first][second];

        long long skip = solve(nums, i + 1, first, second);

        long long take1 = solve(nums, i + 1, std::gcd(first, nums[i]), second);

        long long take2 = solve(nums, i + 1, first, std::gcd(second, nums[i]));

        return dp[i][first][second] =
            (skip + take1 + take2) % MOD;
    }

    int subsequencePairCount(vector<int>& nums) {

        memset(dp, -1, sizeof(dp));

        return (int)solve(nums, 0, 0, 0);
    }
};