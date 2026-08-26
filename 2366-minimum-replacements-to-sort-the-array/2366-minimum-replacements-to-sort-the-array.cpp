class Solution {
public:

    typedef long long ll;

    ll minimumReplacement(vector<int>& nums) {
        
        int n = nums.size();

        ll ops = 0;

        for(int i = n - 2; i >= 0; i--){

            if(nums[i] <= nums[i + 1])
                continue;

            int parts = nums[i] / nums[i + 1];

            if(nums[i] % nums[i + 1] != 0)
                parts++;

            ops += parts - 1;

            nums[i] = nums[i] / parts;
        }

        return ops;
    }
};