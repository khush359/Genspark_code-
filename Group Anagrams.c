
typedef struct {
    char *key;      
    char *orig;     
} Pair;

static int cmp_pairs(const void *a, const void *b) {
    const Pair *pa = (const Pair *)a;
    const Pair *pb = (const Pair *)b;
    return strcmp(pa->key, pb->key);
}

static int cmp_char(const void *a, const void *b) {
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;
    return (ca > cb) - (ca < cb);
}

static char *sorted_copy(const char *s) {
    size_t n = strlen(s);
    char *buf = (char *)malloc(n + 1);
    memcpy(buf, s, n + 1);
    qsort(buf, n, sizeof(char), cmp_char);
    return buf;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Build (sorted_key, original_string) pairs
    Pair *pairs = (Pair *)malloc(sizeof(Pair) * strsSize);
    for (int i = 0; i < strsSize; ++i) {
        pairs[i].key  = sorted_copy(strs[i]);
        pairs[i].orig = strs[i];               
    }

    // Sort pairs by key so anagrams become contiguous
    qsort(pairs, strsSize, sizeof(Pair), cmp_pairs);

    // First pass: count number of groups
    int groups = 0;
    for (int i = 0; i < strsSize; ) {
        int j = i + 1;
        while (j < strsSize && strcmp(pairs[i].key, pairs[j].key) == 0) j++;
        groups++;
        i = j;
    }

    // Allocate outputs
    char ***result = (char ***)malloc(sizeof(char **) * groups);
    int *colSizes = (int *)malloc(sizeof(int) * groups);

    // Second pass: fill groups
    int g = 0;
    for (int i = 0; i < strsSize; ) {
        int j = i + 1;
        while (j < strsSize && strcmp(pairs[i].key, pairs[j].key) == 0) j++;
        int sz = j - i;

        colSizes[g] = sz;
        result[g] = (char **)malloc(sizeof(char *) * sz);
        for (int k = 0; k < sz; ++k) {
            result[g][k] = pairs[i + k].orig;  // point to original strings
        }
        g++;
        i = j;
    }

   
    for (int i = 0; i < strsSize; ++i) free(pairs[i].key);
    free(pairs);

    *returnSize = groups;
    *returnColumnSizes = colSizes;
    return result;
}
