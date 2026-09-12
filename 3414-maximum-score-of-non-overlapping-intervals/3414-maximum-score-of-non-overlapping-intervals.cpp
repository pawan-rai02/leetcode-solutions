class Solution {
public:

    int n;
    vector<int> nxtIdx;

    struct Node {
        long long score = 0;
        vector<int> idxs;
    };

    vector<vector<Node>> dp;
    vector<vector<bool>> vis;

    int findNxt(vector<vector<int>>& intervals, int r) {

        int lo = 0;
        int hi = n - 1;
        int res = n;

        while (lo <= hi) {

            int mid = lo + (hi - lo) / 2;

            if (intervals[mid][0] > r) {
                res = mid;
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        return res;
    }

    Node solve(vector<vector<int>>& intervals, int i, int k) {

        if (k == 0 || i >= n)
            return Node();

        if (vis[i][k])
            return dp[i][k];

        vis[i][k] = true;

        // Don't take current interval
        Node skip = solve(intervals, i + 1, k);

        // Take current interval
        int wt = intervals[i][2];
        int idx = intervals[i][3];
        int j = nxtIdx[i];

        Node temp = solve(intervals, j, k - 1);

        Node take;
        take.score = temp.score + wt;
        take.idxs = temp.idxs;
        take.idxs.push_back(idx);

        sort(take.idxs.begin(), take.idxs.end());

        Node res;

        if (skip.score > take.score) {
            res = skip;
        }
        else if (skip.score < take.score) {
            res = take;
        }
        else {
            res = (skip.idxs < take.idxs) ? skip : take;
        }

        return dp[i][k] = res;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        n = intervals.size();

        for (int i = 0; i < n; i++)
            intervals[i].push_back(i);

        sort(intervals.begin(), intervals.end());

        nxtIdx.resize(n);

        for (int i = 0; i < n; i++) {
            int end = intervals[i][1];
            nxtIdx[i] = findNxt(intervals, end);
        }

        int K = 4;

        dp.resize(n, vector<Node>(K + 1));
        vis.resize(n, vector<bool>(K + 1, false));

        return solve(intervals, 0, K).idxs;
    }
};