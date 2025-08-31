
static int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a, y = *(const int*)b;
    return (x > y) - (x < y);
}


static int lower_bound_int(const int *arr, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < x) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}


static inline int lowbit(int x){ return x & -x; }

static int bit_sum(int *bit, int i) {
    int s = 0;
    while (i > 0) { s += bit[i]; i -= lowbit(i); }
    return s;
}

static void bit_add(int *bit, int n, int i, int delta) {
    while (i <= n) { bit[i] += delta; i += lowbit(i); }
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int n = numsSize;
    *returnSize = n;
    int *ans = (int*)calloc(n, sizeof(int));
    if (n == 0) return ans;

   
    int *vals = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) vals[i] = nums[i];
    qsort(vals, n, sizeof(int), cmp_int);
    int m = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || vals[i] != vals[i-1]) vals[m++] = vals[i];
    }

    int *bit = (int*)calloc((size_t)(m + 1), sizeof(int));

   
    for (int i = n - 1; i >= 0; --i) {
        int x = nums[i];
        int r = lower_bound_int(vals, m, x) + 1;    
        ans[i] = bit_sum(bit, r - 1);              
        bit_add(bit, m, r, 1);                   
    }

    free(bit);
    free(vals);
    return ans;
}
