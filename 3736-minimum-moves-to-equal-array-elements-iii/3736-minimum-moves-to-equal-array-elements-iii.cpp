class Solution {
public:
    int minMoves(vector<int>& nums) {

        int n = nums.size();

        int res = 0;

        int maxValue = *max_element(begin(nums), end(nums));

        for(int &x : nums)
                res += (maxValue - x);


        return res;
    }
};