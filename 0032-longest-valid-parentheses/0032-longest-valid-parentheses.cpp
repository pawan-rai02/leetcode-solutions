class Solution {
public:
    int longestValidParentheses(string s) {

        int open = 0, close = 0;
        int res = 0;

        // Left -> Right
        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(')
                open++;
            else
                close++;

            if (open == close)
                res = max(res, 2 * close);

            else if (close > open)
                open = close = 0;
        }

        open = close = 0;

        // Right -> Left
        for (int i = s.size() - 1; i >= 0; i--) {

            if (s[i] == '(')
                open++;
            else
                close++;

            if (open == close)
                res = max(res, 2 * open);

            else if (open > close)
                open = close = 0;
        }

        return res;
    }
};