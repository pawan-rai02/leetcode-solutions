class Solution {
public:

    int dfsHt(TreeNode* root){

        if(!root)
            return 0;

        int leftHt  = dfsHt(root->left);

        if(leftHt == -1)
            return -1;

        int rightHt = dfsHt(root->right);

        if(rightHt == -1)
            return -1;

        if(abs(leftHt - rightHt) > 1)
            return -1;


        return max(leftHt, rightHt) + 1;
    }

    bool isBalanced(TreeNode* root) {
        
        return dfsHt(root) != -1;
    }
};