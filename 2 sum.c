/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    int key;     // the number from nums
    int value;   // its index
    int used;    // flag: 0 = empty, 1 = used
} HashEntry;

#define HASH_SIZE 100003  // large prime to reduce collisions

static int hashFunc(int key) {
    if (key < 0) key = -key;
    return key % HASH_SIZE;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashEntry* table = (HashEntry*)calloc(HASH_SIZE, sizeof(HashEntry));
    int* result = (int*)malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];

        // Search for complement in hash table
        int h = hashFunc(complement);
        while (table[h].used) {
            if (table[h].key == complement) {
                result[0] = table[h].value;
                result[1] = i;
                *returnSize = 2;
                free(table);
                return result;
            }
            h = (h + 1) % HASH_SIZE; // linear probing
        }

        // Insert current number into hash table
        h = hashFunc(nums[i]);
        while (table[h].used) {
            h = (h + 1) % HASH_SIZE;
        }
        table[h].key = nums[i];
        table[h].value = i;
        table[h].used = 1;
    }

    *returnSize = 0;
    free(table);
    return NULL; // no solution (though problem guarantees one)
}
