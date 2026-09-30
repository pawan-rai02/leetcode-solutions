class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        
        int n = seq.size();

        vector<int> res(n);

        int d = 0;

        for(int i = 0; i < n; i++){

            if(seq[i] == '('){
                d++;
                res[i] = d % 2 == 0 ? 0 : 1;
            }

            else{
                res[i] = d % 2 == 0 ? 0 : 1;
                d--;
            }
        }

        return res;
    }
};