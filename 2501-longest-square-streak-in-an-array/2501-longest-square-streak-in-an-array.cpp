class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {

        sort(begin(nums), end(nums));

        unordered_map<int, int> mp;
        int ans = 1;

        for (int num : nums) {

            int root = sqrt(num);

            if (1LL * root * root == num && mp.find(root) != mp.end()) {
                mp[num] = mp[root] + 1;
            } else {
                mp[num] = 1;
            }

            ans = max(ans, mp[num]);
        }

        return ans >= 2 ? ans : -1;
    }
};