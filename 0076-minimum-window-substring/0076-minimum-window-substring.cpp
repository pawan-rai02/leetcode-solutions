class Solution {
public:
    string minWindow(string& s, string& t) {
        
        int n = s.size();

        if(t.size() > n)
            return "";

        unordered_map<char, int> mp;

        for(char &c : t)
            mp[c]++;

        int reqChars = t.size();

        int i = 0, j = 0;

        int minWindowSize = INT_MAX;

        int start_i = 0;

        while(j < n){
            char ch = s[j];

            if(mp[ch] > 0)
                reqChars--;
            
            mp[ch]--;

            while(reqChars == 0){
                
                // shrink
                int currWs = j - i + 1;

                if(minWindowSize > currWs){
                    minWindowSize = currWs;
                    start_i = i;
                }

                mp[s[i]]++;

                if(mp[s[i]] > 0)    
                    reqChars++;

                i++;
            }

            j++;
        }

        return minWindowSize == INT_MAX ? "" : s.substr(start_i, minWindowSize);

    }
};
