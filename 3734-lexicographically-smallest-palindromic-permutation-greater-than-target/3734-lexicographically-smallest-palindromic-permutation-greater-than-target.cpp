class Solution {
public:

    char midChar = 0;
    int halfLen = 0;
    string res = "";

    bool solve(string &curr, vector<int> &f, string &target, int i, bool gr) {

        // We have constructed the complete left half
        if (curr.size() == halfLen) {

            string rightHalf = curr;
            reverse(rightHalf.begin(), rightHalf.end());

            string candidate = curr + 
                               (midChar ? string(1, midChar) : "") +
                               rightHalf;

            if (candidate > target) {
                res = candidate;
                return true;
            }

            return false;
        }

        // Try characters in increasing order
        for (char ch = 'a'; ch <= 'z'; ch++) {

            int idx = ch - 'a';

            if (f[idx] == 0)
                continue;

            // If we are still equal to target,
            // choosing a smaller character here can never work.
            if (!gr && ch < target[i])
                continue;

            // If we are equal and choose a larger character,
            // the final palindrome is guaranteed to be greater.
            bool newGr = gr || (ch > target[i]);

            f[idx]--;
            curr.push_back(ch);

            if (solve(curr, f, target, i + 1, newGr))
                return true;

            curr.pop_back();
            f[idx]++;
        }

        return false;
    }


    string lexPalindromicPermutation(string& s, string& target) {

        int n = s.size();

        vector<int> f(26, 0);

        for (char &ch : s)
            f[ch - 'a']++;

        // Check whether a palindrome is possible
        int oddCt = 0;
        midChar = 0;

        for (int c = 0; c < 26; c++) {

            if (f[c] % 2 == 1) {

                oddCt++;

                if (oddCt > 1)
                    return "";

                midChar = char('a' + c);
            }
        }

        // Only half of each character goes into left half
        for (int c = 0; c < 26; c++)
            f[c] /= 2;

        halfLen = n / 2;

        res = "";

        string curr;

        solve(curr, f, target, 0, false);

        return res;
    }
};