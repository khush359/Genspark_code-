
static inline int max2(int a, int b) { return a > b ? a : b; }


int longestCommonSubsequence(const char *text1, const char *text2) {
    if (!text1 || !text2) return 0;
    int m = (int)strlen(text1), n = (int)strlen(text2);
    if (m == 0 || n == 0) return 0;

  
    const char *A = text1, *B = text2;
    int rows = m, cols = n;
    if (n < m) { A = text2; B = text1; rows = n; cols = m; }

  
    int *dp_prev = (int*)calloc(cols + 1, sizeof(int));
    int *dp_curr = (int*)calloc(cols + 1, sizeof(int));
    if (!dp_prev || !dp_curr) { free(dp_prev); free(dp_curr); return 0; }

    for (int i = 1; i <= rows; ++i) {
        char ca = A[i-1];
        for (int j = 1; j <= cols; ++j) {
            char cb = B[j-1];
            if (ca == cb) {
                dp_curr[j] = dp_prev[j-1] + 1;
            } else {
                dp_curr[j] = max2(dp_prev[j], dp_curr[j-1]);
            }
        }
     
        int *tmp = dp_prev; dp_prev = dp_curr; dp_curr = tmp;
      
        memset(dp_curr, 0, (cols + 1) * sizeof(int));
    }

    int ans = dp_prev[cols];
    free(dp_prev);
    free(dp_curr);
    return ans;
}
