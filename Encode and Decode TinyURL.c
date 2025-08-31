static long long NEXT_ID = 1;       
static char **ID2URL = NULL;       
static long long ID2URL_CAP = 0;



static char* xstrdup(const char* s) {
    size_t n = strlen(s);
    char* p = (char*)malloc(n + 1);
    memcpy(p, s, n + 1);
    return p;
}

static void ensure_capacity(long long need_idx) {
    if (need_idx < ID2URL_CAP) return;
    long long new_cap = ID2URL_CAP ? ID2URL_CAP : 8;
    while (new_cap <= need_idx) new_cap <<= 1;
    char **new_arr = (char**)calloc(new_cap, sizeof(char*));
    if (ID2URL) {
        memcpy(new_arr, ID2URL, ID2URL_CAP * sizeof(char*));
        free(ID2URL);
    }
    ID2URL = new_arr;
    ID2URL_CAP = new_cap;
}


static const char B62[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static char* to_base62(long long x) {
    char buf[32]; 
    int i = 0;
    if (x == 0) {
        buf[i++] = '0';
    } else {
        while (x > 0) {
            buf[i++] = B62[x % 62];
            x /= 62;
        }
    }
  
    char* s = (char*)malloc(i + 1);
    for (int j = 0; j < i; ++j) s[j] = buf[i - 1 - j];
    s[i] = '\0';
    return s;
}

static int from_b62_char(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return 10 + (c - 'a');
    if (c >= 'A' && c <= 'Z') return 36 + (c - 'A');
    return -1;
}

static long long from_base62(const char* s) {
    long long v = 0;
    for (const char* p = s; *p; ++p) {
        int d = from_b62_char(*p);
        if (d < 0) break; 
        v = v * 62 + d;
    }
    return v;
}



char* encode(char* longUrl) {
    long long id = NEXT_ID++;
    ensure_capacity(id + 1);
    ID2URL[id] = xstrdup(longUrl);

    char* token = to_base62(id);
    const char* prefix = "http://tinyurl.com/";
    size_t plen = strlen(prefix), tlen = strlen(token);
    char* out = (char*)malloc(plen + tlen + 1);
    memcpy(out, prefix, plen);
    memcpy(out + plen, token, tlen + 1);

    free(token);
    return out; 
}


char* decode(char* shortUrl) {
   
    const char* last = strrchr(shortUrl, '/');
    const char* token = last ? last + 1 : shortUrl;

    long long id = from_base62(token);
    if (id <= 0 || id >= ID2URL_CAP || ID2URL[id] == NULL) {
      
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }
  
    return xstrdup(ID2URL[id]);
}

