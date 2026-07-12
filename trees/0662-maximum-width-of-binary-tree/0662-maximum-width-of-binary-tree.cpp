class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        
        if(!root)
            return 0;

        deque<pair<TreeNode*, unsigned long long>> que;   // change
        que.push_back({root, 0});

        int maxW = 0;

        while(!que.empty()){

            int size = que.size();

            unsigned long long mn = que.front().second;   // add

            auto [f1, i1] = que.front();
            auto [b1, i2] = que.back();

            int width = i2 - i1 + 1;

            maxW = max(maxW, width);

            while(size--){

                auto [node, idx] = que.front();
                que.pop_front();

                idx -= mn;        // add

                if(node->left)
                    que.push_back({node->left, 2*idx + 1});

                if(node->right)
                    que.push_back({node->right, 2*idx + 2});
            }
        }

        return maxW;
    }
};