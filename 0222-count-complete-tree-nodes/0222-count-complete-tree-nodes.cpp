class Solution {
public:
    int countNodes(TreeNode* root) {

        if(!root)
            return 0;
        
        int ct = 0;


        queue<TreeNode*> que;
        que.push(root);

        while(!que.empty()){
            int size = que.size();

            ct += size;

            while(size--){

                auto node = que.front();
                que.pop();

                if(node->left)
                    que.push(node->left);

                if(node->right)
                    que.push(node->right);
            }
        }

        return ct;
    }
};