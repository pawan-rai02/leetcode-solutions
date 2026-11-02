class Solution {
public:
    int minMoves2(vector<int>& nums) {
        
        sort(begin(nums), end(nums));

        int n = nums.size();

        int mid = nums[n / 2];

        int res = 0;

        for(int &x : nums)
            res += abs(x - mid);
        

        return res;


    }
};