#include <stdlib.h>

static long long sort_and_count(long long *sums, long long *buf,
                                int left, int right, long long lower, long long upper) {
    if (right - left <= 1) return 0;              
    int mid = left + (right - left) / 2;

    long long cnt = 0;
    cnt += sort_and_count(sums, buf, left,  mid,  lower, upper);
    cnt += sort_and_count(sums, buf, mid,   right, lower, upper);

    // Count valid ranges: for each i in [left, mid), find j in [mid, right)
    // such that lower <= sums[j] - sums[i] <= upper.
    int j1 = mid, j2 = mid;
    for (int i = left; i < mid; ++i) {
        while (j1 < right && sums[j1] - sums[i] <  lower) ++j1;
        while (j2 < right && sums[j2] - sums[i] <= upper) ++j2;
        cnt += (j2 - j1);
    }

    // Merge step (standard merge of two sorted halves)
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (sums[i] <= sums[j]) buf[k++] = sums[i++];
        else                    buf[k++] = sums[j++];
    }
    while (i < mid)  buf[k++] = sums[i++];
    while (j < right) buf[k++] = sums[j++];
    for (int t = left; t < right; ++t) sums[t] = buf[t];

    return cnt;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    if (numsSize <= 0) return 0;

    // Prefix sums: sums[0] = 0, sums[i+1] = sum(nums[0..i])
    long long *sums = (long long*)malloc((numsSize + 1) * sizeof(long long));
    long long *buf  = (long long*)malloc((numsSize + 1) * sizeof(long long));
    if (!sums || !buf) { free(sums); free(buf); return 0; }

    sums[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        sums[i + 1] = sums[i] + (long long)nums[i];
    }

    long long ans = sort_and_count(sums, buf, 0, numsSize + 1, (long long)lower, (long long)upper);

    free(sums);
    free(buf);
    return (int)ans;  
}
