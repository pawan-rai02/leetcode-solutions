class Solution {
public:
    int maxDiff(int num) {
        string s = to_string(num);

        // ---------- Maximum ----------
        string a = s;
        char ch = 0;

        for(char c : a) {
            if(c != '9') {
                ch = c;
                break;
            }
        }

        if(ch) {
            for(char &c : a) {
                if(c == ch)
                    c = '9';
            }
        }

        // ---------- Minimum ----------
        string b = s;

        if(b[0] != '1') {
            ch = b[0];

            for(char &c : b) {
                if(c == ch)
                    c = '1';
            }
        }
        else {
            ch = 0;

            for(int i = 1; i < b.size(); i++) {
                if(b[i] != '0' && b[i] != '1') {
                    ch = b[i];
                    break;
                }
            }

            if(ch) {
                for(char &c : b) {
                    if(c == ch)
                        c = '0';
                }
            }
        }

        return stoi(a) - stoi(b);
    }
};