class Solution {
public:

    int solve(vector<int>& prefSum, int L, int M){

        int n = prefSum.size();

        int res = 0;
        int maxLeftSum = 0;

        for(int mEnd = L + M - 1; mEnd < n; mEnd++){

            int lEnd      = mEnd - M;
            int lStrtPrev = lEnd - L;

            int mBlockSum = prefSum[mEnd] - prefSum[lEnd];
            int lBlockSum = prefSum[lEnd] - (lStrtPrev < 0 ? 0 : prefSum[lStrtPrev]);

            maxLeftSum = max(maxLeftSum, lBlockSum);

            res = max(res, maxLeftSum + mBlockSum);
        }

        return res;
    }


    int maxSumTwoNoOverlap(vector<int>& nums, int L, int M) {
        
        int n = nums.size();

        vector<int> prefSum(n, 0);

        prefSum[0] = nums[0];
        for(int i = 1; i < n; i++)
            prefSum[i] = prefSum[i - 1] + nums[i];

        return max(solve(prefSum, L, M), solve(prefSum, M, L));
    }
};