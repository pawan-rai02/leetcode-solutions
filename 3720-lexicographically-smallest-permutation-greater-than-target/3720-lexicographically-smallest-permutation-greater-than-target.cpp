class Solution {
public:

    string res = "";

    bool solve(string &curr, vector<int>& count, string &target, int i, bool greater){

        if(i == target.size()){

            if(greater){
                res = curr;
                return true;
            }

            return false;
        }

        for(char ch =  'a'; ch <= 'z'; ch++){

            if(count[ch - 'a'] == 0)
                continue;

            if(!greater && ch < target[i])
                continue;

            curr.push_back(ch);
            count[ch - 'a']--;

            bool isGreater = greater || ch > target[i];

            if(solve(curr, count, target, i + 1, isGreater))
                return true;

            curr.pop_back();
            count[ch - 'a']++;
        }

        return false;
    }


    string lexGreaterPermutation(string& s, string& target) {
        
        vector<int> count(26, 0);

        for(char&ch : s)
            count[ch - 'a']++;

        string curr;

        solve(curr, count, target, 0, false);

        return res;
    }
};