
typedef struct Node {
    int key, value;
    struct Node *prev, *next;   
    struct Node *hnext;        
} Node;

typedef struct {
    int capacity;
    int size;
    int buckets;
    Node **table;             
    Node *head;              
    Node *tail;                
} LRUCache;


static void list_add_after_head(LRUCache *obj, Node *node) {
    node->prev = obj->head;
    node->next = obj->head->next;
    obj->head->next->prev = node;
    obj->head->next = node;
}

static void list_remove(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static Node* list_pop_tail(LRUCache *obj) {
    Node *lru = obj->tail->prev;
    if (lru == obj->head) return NULL; 
    list_remove(lru);
    return lru;
}


static unsigned int hash_u32(unsigned int x) {
    x ^= x >> 16; x *= 0x7feb352dU;
    x ^= x >> 15; x *= 0x846ca68bU;
    x ^= x >> 16;
    return x;
}

static int hash_index(LRUCache *obj, int key) {
   
    return (int)(hash_u32((unsigned int)key) & (obj->buckets - 1));
}

static Node* hash_find(LRUCache *obj, int key) {
    int idx = hash_index(obj, key);
    Node *cur = obj->table[idx];
    while (cur) {
        if (cur->key == key) return cur;
        cur = cur->hnext;
    }
    return NULL;
}

static void hash_insert(LRUCache *obj, Node *node) {
    int idx = hash_index(obj, node->key);
    node->hnext = obj->table[idx];
    obj->table[idx] = node;
}

static void hash_remove(LRUCache *obj, Node *node) {
    int idx = hash_index(obj, node->key);
    Node **pp = &obj->table[idx];
    while (*pp) {
        if (*pp == node) {
            *pp = node->hnext;
            return;
        }
        pp = &((*pp)->hnext);
    }
}


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *obj = (LRUCache*)malloc(sizeof(LRUCache));
    obj->capacity = capacity;
    obj->size = 0;

  
    int b = 1;
    int target = capacity * 2;
    if (target < 16) target = 16;
    while (b < target) b <<= 1;
    obj->buckets = b;

    obj->table = (Node**)calloc(obj->buckets, sizeof(Node*));

  
    obj->head = (Node*)malloc(sizeof(Node));
    obj->tail = (Node*)malloc(sizeof(Node));
    obj->head->prev = NULL;
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;
    obj->tail->next = NULL;

    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (!obj) return -1;
    Node *node = hash_find(obj, key);
    if (!node) return -1;
    // move to head (mark as MRU)
    list_remove(node);
    list_add_after_head(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (!obj || obj->capacity == 0) return;

    Node *node = hash_find(obj, key);
    if (node) {
        node->value = value;
        list_remove(node);
        list_add_after_head(obj, node);
        return;
    }

    
    Node *nnode = (Node*)malloc(sizeof(Node));
    nnode->key = key;
    nnode->value = value;
    nnode->hnext = NULL;

    list_add_after_head(obj, nnode);
    hash_insert(obj, nnode);
    obj->size++;

    if (obj->size > obj->capacity) {
        Node *lru = list_pop_tail(obj);
        if (lru) {
            hash_remove(obj, lru);
            free(lru);
            obj->size--;
        }
    }
}

void lRUCacheFree(LRUCache* obj) {
    if (!obj) return;

   
    Node *cur = obj->head->next;
    while (cur && cur != obj->tail) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }

    free(obj->head);
    free(obj->tail);
    free(obj->table);
    free(obj);
}

