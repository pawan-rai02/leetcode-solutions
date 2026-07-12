class Solution {
public:
    int n;
    vector<int> dp, nxt;

    bool valid(string &a, string &b) {
        if (a.size() != b.size()) return false;

        int diff = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                diff++;
                if (diff > 1) return false;
            }
        }
        return diff == 1;
    }

    int solve(int i, vector<string>& words, vector<int>& groups) {
        if (dp[i] != -1)
            return dp[i];

        dp[i] = 1;
        nxt[i] = -1;

        for (int j = i + 1; j < n; j++) {
            if (groups[i] != groups[j] && valid(words[i], words[j])) {
                int cur = 1 + solve(j, words, groups);
                if (cur > dp[i]) {
                    dp[i] = cur;
                    nxt[i] = j;
                }
            }
        }

        return dp[i];
    }

    vector<string> getWordsInLongestSubsequence(vector<string>& words,
                                                vector<int>& groups) {
        n = words.size();
        dp.assign(n, -1);
        nxt.assign(n, -1);

        int start = 0, best = 0;

        for (int i = 0; i < n; i++) {
            int len = solve(i, words, groups);
            if (len > best) {
                best = len;
                start = i;
            }
        }

        vector<string> ans;
        while (start != -1) {
            ans.push_back(words[start]);
            start = nxt[start];
        }

        return ans;
    }
};