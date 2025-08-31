
typedef struct {
    int n;
    int *mem;  // 0 = free, >0 = mID
} Allocator;

Allocator* allocatorCreate(int n) {
    Allocator *obj = (Allocator *)malloc(sizeof(Allocator));
    obj->n = n;
    obj->mem = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) obj->mem[i] = 0;
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int n = obj->n;
    int run = 0;      
    int start = 0;   
    for (int i = 0; i < n; ++i) {
        if (obj->mem[i] == 0) {
            if (run == 0) start = i;
            run++;
            if (run == size) {
                // allocate from start to start + size - 1
                for (int j = 0; j < size; ++j) obj->mem[start + j] = mID;
                return start;
            }
        } else {
            run = 0;
        }
    }
    return -1; // no block found
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int freed = 0;
    for (int i = 0; i < obj->n; ++i) {
        if (obj->mem[i] == mID) {
            obj->mem[i] = 0;
            freed++;
        }
    }
    return freed;
}

void allocatorFree(Allocator* obj) {
    if (!obj) return;
    free(obj->mem);
    free(obj);
}
