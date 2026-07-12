class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {

        if(root == nullptr)
            return new TreeNode(val);

        
        TreeNode* temp = root;
        TreeNode* prev = nullptr;

        while(temp){
            if(temp->val > val){
                prev = temp;
                temp = temp->left;
            }

            else{
                prev = temp;
                temp = temp->right;
            } 
        }

        if(prev->val > val)
            prev->left = new TreeNode(val);
        else
            prev->right = new TreeNode(val);

        return root;
    }
};