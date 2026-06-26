class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        
        sort(begin(players), end(players));
        sort(begin(trainers), end(trainers));

        int n = players.size();
        int m = trainers.size();

        int i = n - 1;
        int j = m - 1;

        int res = 0;

        while(i >= 0 && j >= 0){

            if(players[i] <= trainers[j]){
                res++;
                i--;
                j--;
            }

            else{
                i--;
            }
        }

        return res;
    }
};