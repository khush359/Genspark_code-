/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
static bool valid(struct TreeNode* node, long long low, long long high) {
    if (!node) return true;
    long long v = node->val;
    if (v <= low || v >= high) return false;           // strict: no duplicates
    return valid(node->left,  low, v) && valid(node->right, v, high);
}

bool isValidBST(struct TreeNode* root) {
    return valid(root, LLONG_MIN, LLONG_MAX);
}
