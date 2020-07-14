#include<stdio.h>
#include<stdlib.h>

#define MAX 100
int stack[MAX];
int top = -1;



int pop(){
    if(top<0){
        printf("stack empty");
        return top;
    }
    return stack[top--];
}
char push(char ch){
    if(MAX -1 == top){
        printf("stack full");
        return 0;
    }
    stack[++top] = ch;
    return 0;
}
int Digit_check(char ch){
    if('0' <= ch && ch <='9')
        return 1;
    else
        return 0;
}

int oper_priority(char ch){
    switch(ch){
        case '(':
        case ')': return 10;
        case '*':
        case '/': return 5;
        case '+':
        case '-': return 2;
    }
    return 0;
}

int stack_oper_priority(char ch){
    switch(ch){
        case '(': return 1;
        case ')': return 10;
        case '*':
        case '/': return 5;
        case '+':
        case '-': return 2;
    }
    return 0;
}

void infix_to_postfix(char *infix, char * postfix){
    int cnt =0, i;
    char ch;
    push(0);
    
    for(i=0; infix[i] != 0; i++){
        ch = infix[i];
        if(Digit_check(ch))
            postfix[cnt++] = ch;
        else{
            if(ch ==')'){
                do{
                    postfix[cnt++] = pop();
                }while(postfix[cnt-1] != '(');
                cnt--;
                continue;
            }
            while(stack_oper_priority(stack[top]) >= oper_priority(ch)){
                postfix[cnt++] = pop();
            }
            push(ch);
        }
    }
    do{
        postfix[cnt++] = pop();
    }while(postfix[cnt -1] != 0);
}

int calc(char * postfix) {
    char op1, op2, ch;
    int i;
    
    for (i = 0; postfix[i] != 0; i++) {
        ch = postfix[i];
        if (Digit_check(ch)) {

            push(ch - '0');
        }
        else {
            op2 = pop();
            op1 = pop();
            switch (ch) {
                case '+':
                    push(op1 + op2);
                    break;
                case '-':
                    push(op1 - op2);
                    break;
                case '*':
                    push(op1 * op2);
                    break;
                case '/':
                    push(op1 / op2);
                    break;
            }
        }
    }
    return pop();
}
int main(){
    char infix[50], postfix[50];
    
    printf("infix expression 입력:");
    get_s(infix, sizeof(infix));
    
    if(infix == 'q')
        return 0;
    
    infix_to_postfix(infix, postfix);
    printf("postfix expression: %s\n", postfix);
    printf("result: %d\n", calc(postfix));
    return 0;
}
