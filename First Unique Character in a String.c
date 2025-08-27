int firstUniqChar(char* s) {
    int c[26] = {0}, size = strlen(s);
    for(int i=0;i<size;i++){
        c[s[i]-'a']++;
    }
    for(int i=0;i<size;i++){
         if(c[s[i]-'a'] == 1)  return i;
    }
    return -1;
}
