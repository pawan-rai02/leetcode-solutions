class Solution {
public:
    typedef long long ll;

    ll sumAndMultiply(int n) {
        
        ll x   = 0;
        ll sum = 0;

        ll pow = 1;

        while(n > 0){

            int ld = n % 10;

            if(ld == 0)
                {n = n / 10; continue;}

            x += (ld * pow);

            sum = sum + ld;

            pow = pow * 10;

            n = n / 10;
        }

        return sum * x;
    }
};