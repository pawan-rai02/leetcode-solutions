class Solution {
public:
    int result = 0;

    int diameterOfBinary(TreeNode* root) {

        if (!root)
            return 0;

        int leftSubTree = diameterOfBinary(root->left);
        int rightSubTree = diameterOfBinary(root->right);

        result = max(result, leftSubTree + rightSubTree);

        return 1 + max(leftSubTree, rightSubTree);
    }

    int diameterOfBinaryTree(TreeNode* root) {

        if (!root)
            return 0;
        
        diameterOfBinary(root);

        return result;
    }
};