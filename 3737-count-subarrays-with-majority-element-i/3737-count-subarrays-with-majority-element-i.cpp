class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {

        int n = nums.size();

        int count = 0;

        for(int i = 0; i < n; i++){

            int freq       = 0;
            int otherCount = 0;

            for(int j = i; j < n; j++){

                if(nums[j] == target)
                        freq++;

                else 
                    otherCount++;

                if(freq > otherCount)
                        count++;
                
                
            }
        }



        return count;
    }
};