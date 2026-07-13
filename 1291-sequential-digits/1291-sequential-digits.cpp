class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        
        queue<long long> que;
        for(int i = 1; i <= 9; i++)
            que.push(i);

        vector<int> res;

        while(!que.empty()){

            long long temp = que.front();
            que.pop();

            if(temp >= low && temp <= high)
                res.push_back((int)temp);

            if(temp > high)
                break;

            int lastDigit = temp % 10;

            if(lastDigit < 9){
                long long next = temp * 10 + (lastDigit + 1);
                que.push(next);
            }
        }

        return res;
    }
};