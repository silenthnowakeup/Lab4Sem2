#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#ifndef LAB4SEM2_INCLUDE_H
#define LAB4SEM2_INCLUDE_H
#define MAX_LINE_LENGTH 1024
#define SIZE 256

typedef struct Node {
    char* question;
    struct Node* yes;
    struct Node* no;
    int index;
} Node;

Node *createNode(const char *question, int index);
void readTreeFromFileHelper(Node* current, FILE* file, int count);
Node* readTreeFromFile(FILE* file);
void destroyNode(Node* node);
void guessObject(Node* node, FILE*,char*);
void saveTree(Node* node, FILE* file);
Node *findNode(Node *node, int node_num);
void printTree(Node *root);
char* inputStr();
#endif //LAB4SEM2_INCLUDE_H
