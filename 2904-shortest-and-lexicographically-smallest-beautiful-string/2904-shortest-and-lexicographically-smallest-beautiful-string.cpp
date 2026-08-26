class Solution {
public:
    string shortestBeautifulSubstring(string& s, int k) {
        
        int n = s.size();

        for(int len = k; len <= n; len++){

            string res = "";

            for(int strt = 0; strt <= n - len; strt++){

                string temp = s.substr(strt, len);

                int ones = 0;

                for(char &ch : temp){
                    ones += (ch == '1') ? 1 : 0;
                }

                if(ones == k){
                    if(res.empty() || temp < res)
                        res = temp;
                }
            }

            if(!res.empty())
                return res;
        }
        
        return "";
    }
};