/*
SFWRENG 2S03 Assignment #3
Author: Yousam Asham
MacID: ashamy1
Student Number: 400174082
Filename: expr.c
*/
#include "expr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *makeString(char *s1, char *s2, char *s3) {
  int j = strlen(s1) + strlen(s2) + strlen(s3) + 1;
  char *array = malloc(j);
  if (array == NULL)
    return NULL;
  strcat(strcat(strcpy(array, s1), s2), s3);
  return array;
}
Node *createNode(char *s, double val) {
  Node *head = calloc(sizeof(Node), 1);
  if (head == NULL)
    return NULL;
  head->operation = 0;
  head->value = val;
  if (s != NULL) {
    char *tmp = malloc(strlen(s) + 1);
    strcpy(tmp, s);
    head->expr_string = malloc(strlen(tmp) + 1);
    strcpy(head->expr_string, tmp);
    free(tmp);
  } else
    head->expr_string = NULL;
  head->num_parents = 0;
  return head;
}
Node *binop(Operation op, Node *a, Node *b) {
  Node *ophead = calloc(sizeof(Node), 1);
  if (ophead == NULL)
    return NULL;
  if (a->num_parents == 1 || b->num_parents == 1)
    return NULL;
  ophead->operation = op;
  ophead->left = a;
  ophead->right = b;
  a->num_parents++;
  b->num_parents++;
  ophead->value = 0;
  if (op == addop)
    ophead->expr_string = makeString(a->expr_string, "+", b->expr_string);
  if (op == subop)
    ophead->expr_string = makeString(a->expr_string, "-", b->expr_string);
  if (op == mulop) {
    char *beginning = makeString("(", a->expr_string, ")");
    char *end = makeString("(", b->expr_string, ")");
    ophead->expr_string = makeString(beginning, "*", end);
    free(beginning);
    free(end);
  }
  if (op == divop) {
    char *beginning = makeString("(", a->expr_string, ")");
    char *end = makeString("(", b->expr_string, ")");
    ophead->expr_string = makeString(beginning, "/", end);
    free(beginning);
    free(end);
  }

  return ophead;
}
double evalTree(Node *root) {
  if (root == NULL)
    return 0;
  if ((root->left) == NULL && (root->left) == NULL)
    return root->value;
  double leftAnswer = evalTree(root->left);
  double rightAnswer = evalTree(root->right);
  switch (root->operation) {
  case addop:
    root->value = leftAnswer + rightAnswer;
    return leftAnswer + rightAnswer;
  case subop:
    root->value = leftAnswer - rightAnswer;
    return leftAnswer - rightAnswer;
  case mulop:
    root->value = leftAnswer * rightAnswer;
    return leftAnswer * rightAnswer;
  case divop:
    root->value = leftAnswer / rightAnswer;
    return leftAnswer / rightAnswer;
  }
  return 0;
}
void freeTree(Node *root) {
  if (root == NULL)
    return;
  freeTree(root->left);
  freeTree(root->right);
  free(root->expr_string);
  free(root);
}
Node *duplicateTree(Node *root) {
  if (root == NULL)
    return NULL;
  Node *newNode = createNode(root->expr_string, root->value);
  newNode->operation = root->operation;
  newNode->num_parents = root->num_parents;
  newNode->left = duplicateTree(root->left);
  newNode->right = duplicateTree(root->right);
  return newNode;
}
void printTree(Node *root) {
  if (root == NULL)
    return;
  printf(
      "Node\n   expr_string = %s\n   value       = %g\n   num_parents = %d\n",
      root->expr_string, root->value, root->num_parents);
  printTree(root->left);
  printTree(root->right);
}
