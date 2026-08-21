class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        
        int n = nums.size();

        int resXor = 0;
        bool all0  = true;

        for(int &x : nums){
            resXor = (resXor ^ x);

            if(x != 0)
                all0 = false;
        }
        if(all0)
            return false;

        return (resXor == 0) ? n - 1 : n;
    }
};