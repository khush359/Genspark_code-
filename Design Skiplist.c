
#define SKIPLIST_MAX_LEVEL 32

typedef struct SkipNode {
    int val;
    int level; 
    struct SkipNode* forward[SKIPLIST_MAX_LEVEL];
} SkipNode;

typedef struct {
    SkipNode* head;   
    int level;       
    int size;        
} Skiplist;


static SkipNode* new_node(int val, int level) {
    SkipNode* n = (SkipNode*)malloc(sizeof(SkipNode));
    if (!n) return NULL;
    n->val = val;
    n->level = level;
    for (int i = 0; i < SKIPLIST_MAX_LEVEL; ++i) n->forward[i] = NULL;
    return n;
}

static int random_level(void) {
    
    int lvl = 1;
    while (lvl < SKIPLIST_MAX_LEVEL && (rand() & 1)) ++lvl;
    return lvl;
}



Skiplist* skiplistCreate() {
   
    Skiplist* sl = (Skiplist*)malloc(sizeof(Skiplist));
    if (!sl) return NULL;
    sl->level = 1;
    sl->size = 0;

    sl->head = new_node(INT_MIN, SKIPLIST_MAX_LEVEL); 
    return sl;
}

bool skiplistSearch(Skiplist* obj, int target) {
    if (!obj) return false;
    SkipNode* x = obj->head;
    for (int i = obj->level - 1; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->val < target) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    return (x && x->val == target);
}

void skiplistAdd(Skiplist* obj, int num) {
    if (!obj) return;
    SkipNode* update[SKIPLIST_MAX_LEVEL];
    SkipNode* x = obj->head;

    for (int i = obj->level - 1; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->val < num) {
            x = x->forward[i];
        }
        update[i] = x;
    }

    int lvl = random_level();
    if (lvl > obj->level) {
       for (int i = obj->level; i < lvl; ++i) {
            update[i] = obj->head;
        }
        obj->level = lvl;
    }

    SkipNode* n = new_node(num, lvl);
   for (int i = 0; i < lvl; ++i) {
        n->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = n;
    }
    obj->size++;
}

bool skiplistErase(Skiplist* obj, int num) {
    if (!obj) return false;
    SkipNode* update[SKIPLIST_MAX_LEVEL];
    SkipNode* x = obj->head;

    for (int i = obj->level - 1; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->val < num) {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];
    if (!x || x->val != num) return false; // not found

    for (int i = 0; i < obj->level; ++i) {
        if (update[i]->forward[i] == x) {
            update[i]->forward[i] = x->forward[i];
        }
    }
    free(x);
    obj->size--;

   while (obj->level > 1 && obj->head->forward[obj->level - 1] == NULL) {
        obj->level--;
    }
    return true;
}

void skiplistFree(Skiplist* obj) {
    if (!obj) return;
    SkipNode* cur = obj->head->forward[0];
    while (cur) {
        SkipNode* nxt = cur->forward[0];
        free(cur);
        cur = nxt;
    }
    free(obj->head);
    free(obj);
}
