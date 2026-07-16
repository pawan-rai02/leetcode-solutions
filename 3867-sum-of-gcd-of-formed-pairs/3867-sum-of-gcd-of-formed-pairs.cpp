class Solution {
public:

    typedef long long ll;

    ll gcd(ll a, ll b){
        while(b){

            ll t = a % b;
            a = b;
            b = t;
        }

        return a;
    }

    
    ll gcdSum(vector<int>& nums) {

        int n = nums.size();

        vector<ll> pf(n);

        ll mx = 0;

        for(int i = 0; i < n; i++){
            mx = max(mx, (ll)nums[i]);
            pf[i] = gcd(nums[i], mx);
        }

        sort(begin(pf), end(pf));

        int l = 0, r = n - 1;

        ll res = 0;

        while(l < r){
            res += gcd(pf[l], pf[r]);
            l++;
            r--;
        }

        return res;
    }
};