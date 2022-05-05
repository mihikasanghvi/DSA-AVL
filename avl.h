#include <stdio.h>
#include <stdlib.h>
// AVL tree node
struct AVLTree {
    struct AVLTree* left;
    struct AVLTree* right;
    char *month;
    struct AVLTree* par;
    int height;
    //int bf;
};

struct AVLTree *newNode(char *m);
int max(int a, int b);
int getHeight(struct AVLTree *n);
int getBalanceFactor(struct AVLTree *n);
void Updateheight(struct AVLTree* root);
struct AVLTree* LLR(struct AVLTree* root);
struct AVLTree* RRR(struct AVLTree* root);
struct AVLTree* LRR(struct AVLTree* root);
struct AVLTree* RLR(struct AVLTree* root);
struct AVLTree* Insert(struct AVLTree* root,struct AVLTree* parent,char *month);
void printpreorder(struct AVLTree* root);
struct AVLTree* Balance(struct AVLTree* root);
struct AVLTree* Delete(struct AVLTree* root,char *month);
void deleteTree(struct AVLTree* node);
