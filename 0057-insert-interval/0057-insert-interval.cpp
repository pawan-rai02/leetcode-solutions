class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {

        vector<vector<int>> res;

        int newS = newInterval[0];
        int newE = newInterval[1];

        bool inserted = false;

        for (auto &it : intervals) {

            int currS = it[0];
            int currE = it[1];

            // Current interval completely before new interval
            if (currE < newS) {
                res.push_back(it);
            }

            // Current interval completely after new interval
            else if (currS > newE) {

                if (!inserted) {
                    res.push_back({newS, newE});
                    inserted = true;
                }

                res.push_back(it);
            }

            // Overlapping
            else {
                newS = min(newS, currS);
                newE = max(newE, currE);
            }
        }

        if (!inserted)
            res.push_back({newS, newE});

        return res;
    }
};