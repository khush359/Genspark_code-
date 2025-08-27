/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    int outSize = numsSize - k + 1;
    int *ans = (int*)malloc(sizeof(int) * outSize);
    int *dq = (int*)malloc(sizeof(int) * numsSize); // will store indices
    int front = 0, back = 0; // deque is dq[front..back-1]
    int idx = 0;

    for (int i = 0; i < numsSize; ++i) {
        // 1) Remove indices that are out of this window (i - k + 1 is left bound)
        while (front < back && dq[front] <= i - k) front++;

        // 2) Maintain decreasing order: pop smaller/equal values from the back
        while (front < back && nums[dq[back - 1]] <= nums[i]) back--;

        // 3) Push current index
        dq[back++] = i;

        // 4) Record answer once the first full window is formed
        if (i >= k - 1) {
            ans[idx++] = nums[dq[front]];
        }
    }

    free(dq);
    *returnSize = outSize;
    return ans;
}
