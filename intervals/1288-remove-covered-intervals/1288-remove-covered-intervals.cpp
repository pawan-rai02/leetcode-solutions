class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        
        sort(begin(intervals), end(intervals), [](auto &a, auto &b){
            if(a[0] != b[0])
                return a[0] < b[0];
            
            return b[1] < a[1];
        });

        int count = 1;

        int prev_strt = intervals[0][0];
        int prev_end  = intervals[0][1];

        for(int i = 1; i < intervals.size(); i++){

            int curr_strt = intervals[i][0];
            int curr_end  = intervals[i][1];

            if(prev_end >= curr_strt && curr_end <= prev_end)
                continue;

            count++;
            prev_strt = curr_strt;
            prev_end  = curr_end;
        }

        return count;
    }
};