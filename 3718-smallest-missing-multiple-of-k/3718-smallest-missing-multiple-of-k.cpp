class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {

        set<int> st;

        for(auto &num : nums){
            if(num % k == 0){
                st.insert(num);
            }
        }

        int n = k;

        while(true){
            
            if(st.find(n) == st.end())
                    return n;

            n = n + k;
        }

        return -1;
            
    }
};