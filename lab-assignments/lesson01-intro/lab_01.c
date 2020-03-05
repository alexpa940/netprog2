#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
 
int tok;
double tokval;
 
int next() {
    for (;;) {
        int c = getchar();
        if (c == EOF || strchr("+*\n", c) != NULL) return tok = c;
        if (isspace(c)) continue;
        if (isdigit(c) || c == '.') {
            ungetc(c, stdin);
            scanf(" %lf", &tokval);
            return tok = 'n';
        }
        fprintf(stderr, "Bad character: %c\n", c); abort();
    }
}
 
void skip(int t) { assert(tok == t); next(); }
 
double expr();
 
double numpar() {
    if (tok == 'n') { double x = tokval; skip('n'); return x; }
    double x = expr(); 
    return x;
}
 
double term() {
    double x = numpar();
    for (;;) {
        if (tok == '*') { skip('*'); x *= numpar(); }
        else return x;
    }
}

double expr() {
    double x = term();
    for (;;) {
        if (tok == '+') { skip('+'); x += term(); }
        else return x;
    }
}
 
int main() {
    next();
    while (tok != EOF) {
        if (tok == '\n') { skip('\n'); continue; }
        printf("%.9g\n", expr());
    }
    return 0;
}