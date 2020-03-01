#ifndef EXPR_H
#define EXPR_H

typedef enum {
    addop = 0,    /* encodes addition */
    subop,        /* subtraction */
    mulop,        /* multipllicaiton */
    divop         /* division */
} Operation;

struct node {
    Operation operation;
    double value;
    char* expr_string;
    int num_parents;
    struct node *left, *right;
};

typedef struct node Node;

char* makeString(char* s1, char* s2, char* s3);
Node* createNode(char* s, double val);
Node* binop(Operation op, Node* a, Node* b);
double evalTree(Node* root);
void freeTree(Node* root);
Node* duplicateTree(Node* root);
void printTree(Node* root);

#endif
