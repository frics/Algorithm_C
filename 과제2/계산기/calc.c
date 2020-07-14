#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element;

typedef struct stackNode {
    element data;
    struct stackNode* link;
} stackNode;

stackNode* top;

int isEmpty() {
    if (top == NULL)
        return 1;
    else return 0;
}

void topMakeNull() {
    stackNode* temp;
    while (top != NULL)
        {
        temp = top;
        top = top->link;
        free(temp);
        }
}

void push(element item) {
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
    temp->data = item;
    temp->link = top;
    top = temp;
}

element pop() {
    element item;
    stackNode* temp = top;
    
    if (top == NULL) {
        printf("\n\nStack is empty! \n");
        return 0;
    }
    else {
        item = temp->data;
        top = temp->link;
        free(temp);
        return item;
    }
}

int Digit_check(char ch) {
    if ('0' <= ch && ch <= '9')
        return 1;
    else
        return 0;
}

int oper_priority(char ch) {
    switch (ch) {
        case '(':
        case ')': return 10;
        case '*':
        case '/': return 5;
        case '+':
        case '-': return 2;
    }
    return 0;
}

int stack_oper_priority(char ch) {
    switch (ch) {
        case '(': return 1;
        case ')': return 10;
        case '*':
        case '/': return 5;
        case '+':
        case '-': return 2;
    }
    return 0;
}

int testPair(char* exp) {
    
    topMakeNull();
    char symbol, open_pair;
    
    int i, length = strlen(exp);
    top = NULL;
    
    for (i = 0; i < length; i++) {
        symbol = exp[i];
        switch (symbol) {
            case '(':
                push(symbol);
                break;
            case ')':
                if (top == NULL)
                    return 0;
                else {
                    open_pair = pop();
                    if (open_pair == '(' && symbol != ')')
                        return 0;
                    else
                        break;
                }
        }
    }
    if (top == NULL)
        return 1;
    else
        return 0;
}

void infix_to_postfix(char* infix, char* postfix) {
    int cnt = 0, i;
    char ch;
    push(0);
    for (i = 0; infix[i] != 0; i++) {
        ch = infix[i];
        if (Digit_check(ch))
            postfix[cnt++] = ch;
        else {
            if (ch == ')') {
                do {
                    postfix[cnt++] = pop();
                } while (postfix[cnt - 1] != '(');
                cnt--;
                continue;
            }
            while (stack_oper_priority(top) >= oper_priority(ch)) {
                postfix[cnt++] = pop();
            }
            push(ch);
        }
    }
    do {
        postfix[cnt++] = pop();
    } while (postfix[cnt - 1] != 0);
}

element evalPostfix(char* exp) {
    topMakeNull();
    int opr1, opr2, value, i = 0;
    
    int len = strlen(exp);
    char symbol;
    top = NULL;
    
    for (i = 0; i < len; i++) {
        symbol = exp[i];
        if (symbol >= '0' && symbol <= '9') {
            value = symbol - '0';
            push(value);
        }
        else {
            opr2 = pop();
            opr1 = pop();
            
            switch (symbol) {
                case '+':
                    push(opr1 + opr2);
                    break;
                case '-':
                    push(opr1 - opr2);
                    break;
                case '*':
                    push(opr1 * opr2);
                    break;
                case '/':
                    push(opr1 / opr2);
                    break;
            }
        }
    }
    return pop();
}

int main(){
    char infix[100];
    char postfix[100];
    int result;
    while (1) {
        printf("infix expression:");
        gets(infix, 100);
        
        if (infix[0] == 'q')
            break;
        if (testPair(infix) != 1)
            printf("\nERROR\n");
        
        infix_to_postfix(infix, postfix);
        printf("\n postfix expression: %s", postfix);
        
        result = evalPostfix(postfix);
        printf("\n\n계산결과: %d\n", result);
    }
    printf("\n(프로그램 종료)\n");
    
    return 0;
}

