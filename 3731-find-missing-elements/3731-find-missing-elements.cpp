class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {

        int n = nums.size();

        sort(begin(nums), end(nums));

        vector<int> res;

        int idx = 0;

        for(int i = nums[0]; i < nums[n - 1]; i++){

            if(idx < n && nums[idx] == i)
                idx++;
                
            else res.push_back(i);
        }



        return res;
    }
};