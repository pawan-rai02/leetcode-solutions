class Solution {
public:
    string shortestBeautifulSubstring(string& s, int k) {

        int n = s.size();

        int left = 0;
        int ones = 0;

        string res = "";
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {

            if (s[right] == '1')
                ones++;

            while (ones > k) {
                if (s[left] == '1')
                    ones--;
                left++;
            }

            if (ones == k) {

                while (s[left] == '0')
                    left++;

                int currLen = right - left + 1;

                string temp = s.substr(left, currLen);

                if (currLen < minLen) {
                    minLen = currLen;
                    res = temp;
                }
                else if (currLen == minLen) {
                    res = min(res, temp);
                }
            }
        }

        return res;
    }
};