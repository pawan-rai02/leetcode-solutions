class Solution {
public:
    int numberOfSubstrings(string s) {
        
        int n = s.size();

        int right = 0;
        int left  = 0;

        int count = 0;

        vector<int> freq(3, 0);

        while(right <  n){

            char c = s[right];
            
            freq[c - 'a']++;

            
            while(freq[0] > 0 && freq[1] > 0 && freq[2] > 0){

                count += n - right;

                freq[s[left] - 'a']--;
                left++;
            }

            right++;
        }

        return count;
    }
};