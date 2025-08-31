
void inorderHelper(struct TreeNode* root, int* res, int* idx) {
    if (root == NULL) return;
    inorderHelper(root->left, res, idx);
    res[(*idx)++] = root->val;
    inorderHelper(root->right, res, idx);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
   
    int* res = (int*)malloc(10000 * sizeof(int)); 
    *returnSize = 0;

    inorderHelper(root, res, returnSize);
    return res;
}
