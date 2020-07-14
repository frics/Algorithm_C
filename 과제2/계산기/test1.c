#include<stdio.h>
#include<string.h>

#define MAX 10

typedef struct {
    int top;
    int stack[MAX];
} Stack;

void init(Stack* s);
int empty(Stack* s);
int full(Stack* s);
void push(Stack* s, int val);
char pop(Stack*s);
char peek(Stack* s);
int prec(char ch);
int calc(char form[]);



void init(Stack* s) {
    s->top = -1;
}

int empty(Stack* s) {
    return (s->top == -1);
}
int full(Stack* s) {
    return (s->top == (MAX - 1));
}
void push(Stack* s, int val) {
    if (full(s)) {
        printf("stack overflow\n");
        return;
    }
    s->stack[++(s->top)] = val;
}
char pop(Stack* s) {
    if (empty(s)) {
        printf("stack underflow\n");
        return -1;
    }
    return s->stack[(s->top)--];
}
char peek(Stack* s) {
    if (empty(s)) {
        printf("stack underflow\n");
        return -1;
    }
    return s->stack[s->top];
}

int prec(char ch) {
    if (ch == '+' || ch == '-')
        return 3;
    else if (ch == '*' || ch == '/')
        return 4;
    else if (ch == ')')
        return 2;
    else if (ch == '(')
        return 1;
}

int calc(char form[]) {
    int op1, op2, result, i = 0;
    int len = strlen(form);
    char ch;
    Stack s;
    
    init(&s);
    
    for (i = 0; i < len; i++) {
        ch = form[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            result = ch - '0';
            push(&s, result);
        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    break;
            }
        }
    }
    return pop(&s);
}

int main() {
    int i = 0, j = 0, len;
    char express[30];
    char ch, top_operation, form[MAX] = { 0 };
    Stack s;
    init(&s);
    
    printf("수식을 입력하시오:");
    gets(express, );
   
    len = strlen(express);
    
    for (i = 0; i < len; i++) {
        ch = express[i];
        if ((ch == '+') && (ch == '-') && (ch == '*') && (ch == '/')) {
            while (!empty(&s) && (prec(ch) <= prec(peek(&s))))
                form[j++] = pop(&s);
            push(&s, ch);
        }
        else if (ch == '(')
            push(&s, ch);
        
        else if (ch == ')') {
            top_operation = pop(&s);
            while (top_operation != '(') {
                form[j++] = top_operation;
                top_operation = pop(&s);
            }
        }
        else
            form[j++] = ch;
    }
    while (!empty(&s)) {
        form[j++] = pop(&s);
    }
    printf("%s", form);
    printf("계산 결과: %d\n", calc(form));
    
    return 0;
    
}


