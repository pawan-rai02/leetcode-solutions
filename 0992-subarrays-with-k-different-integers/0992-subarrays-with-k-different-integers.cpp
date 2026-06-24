class Solution {
public:             

    int solve(vector<int> &nums, int k){

        int n = nums.size();

        unordered_map<int, int> mp;

        int count = 0;
        int left  = 0;

        for(int r = 0; r < n; r++){

            mp[nums[r]]++;

            while(mp.size() > k){
                mp[nums[left]]--;

                if(mp[nums[left]] == 0)
                    mp.erase(nums[left]);

                left++;
            }

            count += (r - left + 1);
        }
        
        return count;
    }


    int subarraysWithKDistinct(vector<int>& nums, int k) {
        

        return solve(nums, k) - solve(nums, k - 1);
    }
};