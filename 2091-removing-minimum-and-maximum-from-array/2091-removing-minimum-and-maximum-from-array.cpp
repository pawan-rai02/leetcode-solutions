class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        
        int n = nums.size();

        int maxIdx = -1;
        int minIdx = -1;

        int maxEle = INT_MIN;
        int minEle = INT_MAX;

        for(int i = 0; i < n; i++){

            if(nums[i] > maxEle){
                maxEle = nums[i];
                maxIdx = i;
            }

            if(nums[i] < minEle){
                minEle = nums[i];
                minIdx = i;
            }
        }

        int left  = min(minIdx, maxIdx);
        int right = max(minIdx, maxIdx);


        int option1 = right + 1;

        // Remove both from the right
        int option2 = n - left;

        // Remove leftmost from left, rightmost from right
        int option3 = (left + 1) + (n - right);

        return min({option1, option2, option3});
    }
};