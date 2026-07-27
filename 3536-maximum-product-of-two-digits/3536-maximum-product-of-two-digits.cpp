class Solution {
public:
    int maxProduct(int n) {
        
        vector<int> f(10, 0);

        while(n > 0){
            int ld = n % 10;
            f[ld]++;

            n = n / 10;
        }

        int fd = 0;
        int sd = 0;

        for(int i = 9; i >= 0; i--){
            if(f[i] == 0)
                continue;

            if(f[i] > 0 && fd == 0){
                fd = i;
                f[i]--;
            }

            if(f[i] > 0 && sd == 0){
                sd = i;
                f[i]--;
            }
        }

        return fd * sd;
    }
};