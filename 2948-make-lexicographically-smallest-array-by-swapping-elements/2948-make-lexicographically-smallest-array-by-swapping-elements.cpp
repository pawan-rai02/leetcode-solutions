class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {

        int n = nums.size();

        vector<int> vec = nums;       // keep original order

        sort(nums.begin(), nums.end());

        int gn = 0;

        unordered_map<int, int> numToGrp;
        unordered_map<int, list<int>> grpToList;

        numToGrp[nums[0]] = gn;
        grpToList[gn].push_back(nums[0]);

        for (int i = 1; i < n; i++) {

            // nums is sorted, so compare adjacent sorted values
            if (abs(nums[i] - nums[i - 1]) > limit)
                gn++;

            numToGrp[nums[i]] = gn;
            grpToList[gn].push_back(nums[i]);
        }

        vector<int> res(n);

        for (int i = 0; i < n; i++) {

            int num = vec[i];              // original value
            int grp = numToGrp[num];

            // smallest unused number in this group
            res[i] = grpToList[grp].front();
            grpToList[grp].pop_front();
        }

        return res;
    }
};