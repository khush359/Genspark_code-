
/* LeetCode definition:
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
*/

struct Vec {
    struct TreeNode **a;
    int n, cap;
};

static void vec_init(struct Vec *v) {
    v->a = NULL; v->n = 0; v->cap = 0;
}
static void vec_push(struct Vec *v, struct TreeNode *x) {
    if (v->n == v->cap) {
        v->cap = v->cap ? v->cap * 2 : 16;
        v->a = (struct TreeNode**)realloc(v->a, v->cap * sizeof(*v->a));
    }
    v->a[v->n++] = x;
}

static void inorder(struct TreeNode *root, struct Vec *v) {
    if (!root) return;
    inorder(root->left, v);
    vec_push(v, root);
    inorder(root->right, v);
}

static struct TreeNode* build(struct TreeNode **arr, int l, int r) {
    if (l > r) return NULL;
    int m = l + (r - l) / 2;
    struct TreeNode *node = arr[m];
    node->left  = build(arr, l, m - 1);
    node->right = build(arr, m + 1, r);
    return node;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    if (!root) return NULL;
    struct Vec v; vec_init(&v);
    inorder(root, &v);               
    struct TreeNode *newRoot = build(v.a, 0, v.n - 1);  
    free(v.a);
    return newRoot;
}
