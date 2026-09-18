class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {

        int n = s.size();

        vector<int> strt(26, -1);
        vector<int> end(26, -1);

        vector<bool> isValid(26, false);

        vector<string> res;

        // 1. Find first and last occurrence of every character
        for(int i = 0; i < n; i++) {

            int idx = s[i] - 'a';

            if(strt[idx] == -1)
                strt[idx] = i;

            end[idx] = i;
        }


        // 2. Find valid intervals
        for(int c = 0; c < 26; c++) {

            if(strt[c] == -1)
                continue;

            isValid[c] = true;

            for(int i = strt[c]; i <= end[c]; i++) {

                int curr = s[i] - 'a';

                // This character appeared before our starting point
                if(strt[curr] < strt[c]) {
                    isValid[c] = false;
                    break;
                }

                // We must include all occurrences of curr
                end[c] = max(end[c], end[curr]);
            }
        }


        // 3. Select maximum number of non-overlapping intervals
        int lastTakenStrt = INT_MAX;

        for(int i = n - 1; i >= 0; i--) {

            int c = s[i] - 'a';

            if(!isValid[c])
                continue;

            // Only process at first occurrence
            if(i == strt[c] && end[c] < lastTakenStrt) {

                res.push_back(
                    s.substr(i, end[c] - i + 1)
                );

                lastTakenStrt = i;
            }
        }

        reverse(res.begin(), res.end());

        return res;
    }
};