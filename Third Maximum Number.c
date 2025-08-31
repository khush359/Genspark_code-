
int thirdMax(int* nums, int numsSize) {
    long long first = LLONG_MIN, second = LLONG_MIN, third = LLONG_MIN;
    bool has1 = false, has2 = false, has3 = false;

    for (int i = 0; i < numsSize; ++i) {
        long long x = nums[i];

     
        if ((has1 && x == first) || (has2 && x == second) || (has3 && x == third))
            continue;

        if (!has1 || x > first) {
           
            third = second; has3 = has2;
            second = first; has2 = has1;
            first = x;      has1 = true;
        } else if (!has2 || x > second) {
            third = second; has3 = has2;
            second = x;     has2 = true;
        } else if (!has3 || x > third) {
            third = x; has3 = true;
        }
    }

    return has3 ? (int)third : (int)first;
}
