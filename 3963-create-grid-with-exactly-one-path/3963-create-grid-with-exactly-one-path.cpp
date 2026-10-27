class Solution {
public:
    vector<string> createGrid(int m, int n) {
        
        vector<string> res(m);

        string temp = ".";
        string tempL = ".";

        while(n > 1){
            temp.push_back('#');
            tempL.push_back('.');
            n--;
        }

        for(int i = 0; i < m - 1; i++)
            res[i] = temp;

        res[m-1] = tempL;

        return res;
    }
};