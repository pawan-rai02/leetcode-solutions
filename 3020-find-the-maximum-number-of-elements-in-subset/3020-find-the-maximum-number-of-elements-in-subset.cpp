class Solution {
public:

    typedef long long ll;

    int maximumLength(vector<int>& nums) {
        
        unordered_map<ll, int> mp;

        for(int &x : nums)
            mp[x]++;

        int res = 0;

        if(mp[1] % 2 == 1)
            res = mp[1];

        else
            res = mp[1] - 1;

        for(auto &[num, f] : mp){
            if(num == 1)
                continue;

            ll curr = num;
            int len = 0;

            while(mp.count(curr) && mp[curr] > 1){
                len += 2;
                curr = curr * curr;
            }

            if(mp.count(curr) == 1)
                len += 1;
            else len -= 1;

            res = max(res, len);
        }

        return res;
    }
};