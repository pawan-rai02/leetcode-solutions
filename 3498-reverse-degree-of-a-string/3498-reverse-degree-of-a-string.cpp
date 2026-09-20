class Solution {
public:
    int reverseDegree(string& s) {
        
        int res = 0;

        for(int i = 0; i < s.size(); i++){

            int idx = -((s[i] - 'a') - 26) * (i + 1);

            res += idx;
        }

        return res;
    }
};