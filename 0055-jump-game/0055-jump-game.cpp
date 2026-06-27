class Solution {
public:
    bool canJump(vector<int>& nums) {
        
        int n = nums.size();

        int maxEnd = nums[0];

        if(maxEnd >= n - 1)
            return true;

        for(int i = 1; i < n; i++){

            if(maxEnd < i)
                return false;
                
            maxEnd = max(maxEnd, i + nums[i]);

            if(maxEnd >= n - 1)
                return true;
        }

        return false;
    }
};