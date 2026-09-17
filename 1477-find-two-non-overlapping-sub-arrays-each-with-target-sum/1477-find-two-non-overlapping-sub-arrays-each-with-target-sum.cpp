class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {

        int n = arr.size();

        int i = 0;
        int j = 0;

        int currSum = 0;

        vector<int> minBestTillIdx(n, INT_MAX);

        int bstMinLen = INT_MAX;
        int res = INT_MAX;

        while (j < n) {

            currSum += arr[j];

            while (i <= j && currSum > target) {
                currSum -= arr[i];
                i++;
            }

            if (currSum == target) {

                int len = j - i + 1;

                // Best subarray completely before current one
                if (i > 0 && minBestTillIdx[i - 1] != INT_MAX) {
                    res = min(res, len + minBestTillIdx[i - 1]);
                }

                bstMinLen = min(bstMinLen, len);
            }

            // Best subarray ending anywhere <= j
            minBestTillIdx[j] = bstMinLen;

            j++;
        }

        return res == INT_MAX ? -1 : res;
    }
};