class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        
        int n = arr.size();

        int maxele = 0;

        sort(begin(arr), end(arr));

        for(int i = 0; i < n; i++){
            if(i == 0)
                arr[i] = 1;

            else if(abs(arr[i] - arr[i - 1]) > 1)
                arr[i] = arr[i - 1] + 1;

            maxele = max(maxele, arr[i]);
        }

        return maxele;
    }
};