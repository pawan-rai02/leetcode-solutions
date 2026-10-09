class Solution {
public:

    int n;

    unordered_map<char, string> mp = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };


    void bt(int i, string& digits, string& curr, vector<string>& res){

        if(i >= n){
            res.push_back(curr);
            return;
        }
        
        char cd = digits[i];

        for(auto &cc : mp[cd]){
            curr.push_back(cc);

            bt(i + 1, digits, curr, res);

            curr.pop_back();
        }
    }
    vector<string> letterCombinations(string& digits) {

        n = digits.size();
        
        string curr = "";
        vector<string> res;

        bt(0, digits, curr, res);

        return res;
    }
};