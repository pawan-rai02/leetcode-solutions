class Solution {
public:

    bool isPalin(string &s, int i, int j) {

        while (i < j) {
            if (s[i] != s[j])
                return false;

            i++;
            j--;
        }

        return true;
    }

    int maxPalindromes(string& s, int k) {
        
        int n = s.size();

        if(k == 1)
            return n;

        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        for(int i = n - 1; i >= 0; i--){
            for(int j = n - 1; j >= 0; j--){
                if(isPalin(s, i, j)){

                    int takeIt = 1 + (j + k <= n ? dp[j + 1][j + k] : 0);
                    int grow   = dp[i][j + 1];
                    int slide  = dp[i + 1][j + 1];

                    dp[i][j] = max({takeIt, grow, slide});
                }

                int grow  = dp[i][j + 1];
                int slide = dp[i + 1][j + 1];

                dp[i][j] = max({dp[i][j], grow, slide});
            }
        }

        return dp[0][k - 1];
    }
};