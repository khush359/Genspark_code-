bool isValid(char* s) {
     int len = strlen(s);
    char* stack = (char*) malloc(len);
    int top=-1;

    for(int i=0; s[i]!= '\0'; i++){
        char c= s[i];
        if(c=='(' || c=='{' || c=='['){
            stack[++top] = c;
        }
        else{
            if(top == -1) return false;
            if((c==')' && stack[top] != '(') || (c=='}' && stack[top] !='{') ||(c==']' && stack[top] !='[')){
                return false;
            }
            top--;
        }
    }
    return top ==-1;
}
