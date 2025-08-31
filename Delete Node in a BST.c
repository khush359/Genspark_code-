
static struct TreeNode* minNode(struct TreeNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (!root) return NULL;

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
       
        if (!root->left) {
            struct TreeNode* r = root->right;
            free(root);
            return r;
        } else if (!root->right) {
            struct TreeNode* l = root->left;
            free(root);
            return l;
        } else {
          
            struct TreeNode* succ = minNode(root->right);
            root->val = succ->val;  
         
            root->right = deleteNode(root->right, succ->val);
        }
    }
    return root;
}
