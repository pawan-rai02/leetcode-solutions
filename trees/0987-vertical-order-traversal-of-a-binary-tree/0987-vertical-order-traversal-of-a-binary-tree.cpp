class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {

        if (!root)
            return {};

        // col -> {row, value}
        map<int, vector<pair<int, int>>> mp;

        // {node, {row, col}}
        queue<pair<TreeNode*, pair<int, int>>> q;
        q.push({root, {0, 0}});

        while (!q.empty()) {

            auto [node, pos] = q.front();
            q.pop();

            int row = pos.first;
            int col = pos.second;

            mp[col].push_back({row, node->val});

            if (node->left)
                q.push({node->left, {row + 1, col - 1}});

            if (node->right)
                q.push({node->right, {row + 1, col + 1}});
        }

        vector<vector<int>> ans;

        for (auto &[col, vec] : mp) {

            sort(vec.begin(), vec.end());   // sort by row, then value

            vector<int> temp;

            for (auto &[row, val] : vec)
                temp.push_back(val);

            ans.push_back(temp);
        }

        return ans;
    }
};