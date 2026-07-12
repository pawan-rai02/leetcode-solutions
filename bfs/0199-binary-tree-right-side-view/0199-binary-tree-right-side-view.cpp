class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        
        if(!root)
            return {};

        queue<TreeNode*> que;
        que.push(root);

        vector<int> res;
        res.push_back(root->val);

        while(!que.empty()){
            int size = que.size();

            int temp = -1;

            while(size--){
                
                auto node = que.front();
                que.pop();

                if(node->left){
                    que.push(node->left);
                    temp = node->left->val;
                }
                    

                if(node->right){
                    que.push(node->right);
                    temp = node->right->val;
                }
            }

            if(temp != -1)
                res.push_back(temp);
        }


        return res;
    }
};