#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack implementation for characters
char stack[MAX];
int top = -1;

void push(char ch) {
    stack[++top] = ch;
}

char pop() {
    if (top == -1) return -1;
    return stack[top--];
}

char peek() {
    if (top == -1) return -1;
    return stack[top];
}

int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

void infixToPostfix(char* infix, char* postfix) {
    int i, k = 0;
    for(i = 0; infix[i]; i++) {
        if (infix[i] == ' ') continue;

        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top != -1 && peek() != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        } else if (isOperator(infix[i])) {
            while (top != -1 && precedence(peek()) >= precedence(infix[i]))
                postfix[k++] = pop();
            push(infix[i]);
        }
    }

    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
}

void reverse(char* exp) {
    int i, j;
    int len = strlen(exp);
    for (i = 0, j = len - 1; i < j; i++, j--) {
        char temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }
}

void replaceBrackets(char* exp) {
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }
}

void infixToPrefix(char* infix, char* prefix) {
    char revInfix[MAX], revPostfix[MAX];
    strcpy(revInfix, infix);
    reverse(revInfix);
    replaceBrackets(revInfix);
    top = -1; // reset stack
    infixToPostfix(revInfix, revPostfix);
    reverse(revPostfix);
    strcpy(prefix, revPostfix);
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];

    printf("Enter infix expression (e.g., A+(B*C)):\n");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // remove newline

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    infixToPrefix(infix, prefix);
    printf("Prefix: %s\n", prefix);

    return 0;
}
