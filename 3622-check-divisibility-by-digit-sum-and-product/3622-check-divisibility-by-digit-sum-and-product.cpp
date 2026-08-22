class Solution {
public:
    bool checkDivisibility(int n) {

        int temp = n;

        int digitSum  = 0;
        int digitProd = 1;

        while(temp != 0){

            int last = temp % 10;

            digitSum  += last;
            digitProd *= last;

            temp = temp / 10;
        }

        int total = digitSum + digitProd;

        return (n % total == 0);
    }
};