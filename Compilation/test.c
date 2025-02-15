#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
char *input;  // Pointer to input string
char lookahead;  // Current character/token

void nextToken() {
    lookahead = *input++;  // Move to the next character
}

void match(char expected) {
    if (lookahead == expected) {
        nextToken();
    } else {
        printf("Syntax Error: Expected '%c' but found '%c'\n", expected, lookahead);
        exit(1);
    }
}

// Grammar Functions
void E();
void T();
void F();

void E() {
    T();
    if (lookahead == '+') {
        match('+');
        E();
    }
}

void T() {
    F();
    if (lookahead == '*') {
        match('*');
        T();
    }
}

void F() {
    if (lookahead == '(') {
        match('(');
        E();
        match(')');
    } else if (isalpha(lookahead)) {
        match(lookahead);  // Match an identifier (id)
    } else {
        printf("Syntax Error: Unexpected token '%c'\n", lookahead);
        exit(1);
    }
}

int main() {
    input = "(a+b)*c$";  // Example input (end with $ for EOF)
    nextToken();  // Initialize lookahead

    E();  // Start parsing with the starting rule

    if (lookahead == '$') {
        printf("Parsing successful!\n");
    } else {
        printf("Syntax Error: Unexpected token '%c' at the end\n", lookahead);
    }

    return 0;
}
