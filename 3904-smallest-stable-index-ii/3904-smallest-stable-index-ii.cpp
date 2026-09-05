class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {

        int n = nums.size();
        
        vector<int> mx(n, 0);
        vector<int> mn(n, 0);

        int currMx = nums[0];

        for(int i = 0; i < n; i++){

            currMx = max(currMx, nums[i]);
            mx[i] = currMx;
        }

        int currMin = nums[n-1];

        for(int i = n - 1; i >= 0; i--){
            currMin = min(currMin, nums[i]);

            mn[i] = currMin;
        }

        for(int i = 0; i < n; i++){
            int isc = mx[i] - mn[i];

            if(isc <= k){
                return i;
            }
        }

        return -1;
        
    }
};