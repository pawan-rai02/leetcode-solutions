class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        if(!root)
            return {};

        vector<vector<int>> res;
        
        queue<TreeNode*> que;
        que.push(root);

        bool rev = false;

        while(!que.empty()){

            int size = que.size();

            vector<int> temp;

            while(size--){
                auto node = que.front();
                que.pop();

                if(node->left)
                    que.push(node->left);

                if(node->right)
                    que.push(node->right);
                
                temp.push_back(node->val);
            }

            if(rev)
                reverse(begin(temp), end(temp));

            res.push_back(temp);

            rev = !rev;
        }

        return res;


    }
};