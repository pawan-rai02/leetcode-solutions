class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        
        vector<int> sorted = arr;

        sort(begin(sorted), end(sorted), [](int& a, int& b){
            return a < b;
        });

        int rank = 1;

        unordered_map<int, int> mp;
        for(int i = 0; i < arr.size(); i++){

            if(mp.find(sorted[i]) == mp.end())
                mp[sorted[i]] = rank, rank++;
        }

        for(int i = 0; i < arr.size(); i++)
            arr[i] = mp[arr[i]];

        return arr;
    }
};