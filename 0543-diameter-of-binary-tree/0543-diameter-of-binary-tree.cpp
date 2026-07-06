class Solution {
public:

    int max_dia = 0;

    int findH(TreeNode* root){

        if(!root)
            return 0;

        int leftH  = findH(root->left);

        int rightH = findH(root->right);

        max_dia = max(leftH + rightH, max_dia);

        return 1 + max(leftH, rightH);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        
        findH(root);
        return max_dia;
    }
};