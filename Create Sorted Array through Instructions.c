
#include <stdlib.h>
#include <stdint.h>

#define MOD 1000000007


static inline int lowbit(int x) { return x & -x; }

static long long bit_sum(long long *bit, int i) {
    long long s = 0;
    while (i > 0) { s += bit[i]; i -= lowbit(i); }
    return s;
}

static void bit_add(long long *bit, int n, int i, int delta) {
    while (i <= n) { bit[i] += delta; i += lowbit(i); }
}


static int cmp_ll(const void *a, const void *b) {
    long long x = *(const long long*)a, y = *(const long long*)b;
    return (x < y) ? -1 : (x > y);
}

static int lower_bound_ll(const long long *arr, int n, long long x) {
    int lo = 0, hi = n; // first idx >= x
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < x) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int createSortedArray(int* instructions, int instructionsSize){
    int n = instructionsSize;
    if (n == 0) return 0;

   
    long long *vals = (long long*)malloc(sizeof(long long)*n);
    for (int i = 0; i < n; ++i) vals[i] = (long long)instructions[i];

    
    qsort(vals, n, sizeof(long long), cmp_ll);
    int m = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || vals[i] != vals[i-1]) vals[m++] = vals[i];
    }

   
    long long *bit = (long long*)calloc((size_t)(m + 1), sizeof(long long));
    if (!bit) { free(vals); return 0; }

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long x = (long long)instructions[i];
      
        int r = lower_bound_ll(vals, m, x) + 1;

        long long less = bit_sum(bit, r - 1);
        long long leq  = bit_sum(bit, r);
        long long greater = i - leq; 

        ans = (ans + (less < greater ? less : greater)) % MOD;
        bit_add(bit, m, r, 1);
    }

    free(bit);
    free(vals);
    return (int)(ans % MOD);
}
