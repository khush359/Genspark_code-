
static struct ListNode* cursor;  

static int getLength(struct ListNode* head) {
    int n = 0;
    while (head) { n++; head = head->next; }
    return n;
}

static struct TreeNode* buildBST(int left, int right) {
    if (left > right) return NULL;

    int mid = left + (right - left) / 2;

  
    struct TreeNode* L = buildBST(left, mid - 1);

   
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = cursor->val;
    root->left = L;

    
    cursor = cursor->next;

  
    root->right = buildBST(mid + 1, right);

    return root;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {
    int n = getLength(head);
    cursor = head;
    return buildBST(0, n - 1);
}
