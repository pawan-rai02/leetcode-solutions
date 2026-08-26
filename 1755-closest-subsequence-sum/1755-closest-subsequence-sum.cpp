class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        
        int n = nums.size();

        int n1 = n / 2;
        int n2 = n - n1;

        vector<int> sumsA(1 << n1);

        for(int mask = 0; mask < (1 << n1); mask++){
            
            int s = 0;
            for(int i = 0; i < n1; i++){

                if(mask & (1 << i))
                    s += nums[i];
            }

            sumsA[mask] = s;
        }

        vector<int> sumsB(1 << n2);

        for(int mask = 0; mask < (1 << n2); mask++){
            
            int s = 0;
            for(int i = 0; i < n2; i++){

                if(mask & (1 << i))
                    s += nums[n1 + i];
            }

            sumsB[mask] = s;
        }

        sort(begin(sumsB), end(sumsB));

        int minVal = INT_MAX;
        for(int &sum1 : sumsA){

            int need = goal - sum1;
            int low  = lower_bound(begin(sumsB), end(sumsB), need) - begin(sumsB);

            if(low < sumsB.size()){
                int sum2  = sumsB[low];
                int total = sum1 + sum2;
                minVal = min(minVal, abs(total - goal));
            }

            if(low > 0){
                int sum2 = sumsB[low - 1];
                int total = sum1 + sum2;
                minVal = min(minVal, abs(total - goal));
            }
        }

        return minVal;
    }
};