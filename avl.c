#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct AVLTree *newNode(char *m){
    struct AVLTree *nn = (struct AVLTree *)malloc(sizeof(struct AVLTree));
    nn->month = m;
    nn->right = nn->left = nn->par = NULL;
    nn->height=0;
    //nn->bf = 0;
    return nn;
}
/*int updatebf(struct AVLTree *root){
    root->bf = root->left->height - root->right->height;
}*/
int max(int a, int b){
    return a>b?a:b;
}

int getHeight(struct AVLTree *n){
    if(n==NULL){
        return 0;
    }
    return n->height;
}
// Function to update the height of
// a node according to its children's
// node's heights

int getBalanceFactor(struct AVLTree *n){
    if(n==NULL){
        return 0;
    }
    else{
        return getHeight(n->left)-getHeight(n->right);
    }
}

void Updateheight(struct AVLTree* root)
{
    if (root != NULL) {

        // Store the height of the
        // current node
        int val = 1;

        // Store the height of the left
        // and right substree
        if (root->left != NULL)
            val = root->left->height + 1;

        if (root->right != NULL)
            val = max(
                val, root->right->height + 1);

        // Update the height of the
        // current node
        root->height = val;
    }
}

// Function to handle Left Left Case
struct AVLTree* LLR(struct AVLTree* root)
{
    // Create a reference to the
    // left child
    struct AVLTree* temp = root->left;

    // Update the left child of the
    // root to the right child of the
    // current left child of the root
    root->left = temp->right;

    // Update parent pointer of the
    // left child of the root node
    if (temp->right != NULL)
        temp->right->par = root;

    // Update the right child of
    // tmpnode to root
    temp->right = root;

    // Update parent pointer of
    // the tmpnode
    temp->par = root->par;

    // Update the parent pointer
    // of the root
    root->par = temp;

    // Update tmpnode as the left or the
    // right child of its parent pointer
    // according to its key value
    if (temp->par != NULL
        && root->month < temp->par->month) {
        temp->par->left = temp;
    }
    else {
        if (temp->par != NULL)
            temp->par->right = temp;
    }

    // Make tmpnode as the new root
    root = temp;

    // Update the heights
    Updateheight(root->left);
    Updateheight(root->right);
    Updateheight(root);
    Updateheight(root->par);
    //updatebf(root->left);
    //updatebf(root->right);
    //updatebf(root);
    //updatebf(root->par);
    // Return the root node
    return root;
}

// Function to handle Right Right Case
struct AVLTree* RRR(struct AVLTree* root)
{
    // Create a reference to the
    // right child
    struct AVLTree* temp = root->right;

    // Update the right child of the
    // root as the left child of the
    // current right child of the root
    root->right = temp->left;

    // Update parent pointer of the
    // right child of the root node
    if (temp->left != NULL)
        temp->left->par = root;

    // Update the left child of the
    // tmpnode to root
    temp->left = root;

    // Update parent pointer of
    // the tmpnode
    temp->par = root->par;

    // Update the parent pointer
    // of the root
    root->par = temp;

    // Update tmpnode as the left or
    // the right child of its parent
    // pointer according to its key value
    if (temp->par != NULL
        && root->month < temp->par->month) {
        temp->par->left = temp;
    }
    else {
        if (temp->par != NULL)
            temp->par->right = temp;
    }

    // Make tmpnode as the new root
    root = temp;

    // Update the heights
    Updateheight(root->left);
    Updateheight(root->right);
    Updateheight(root);
    Updateheight(root->par);
    //updatebf(root->left);
    //updatebf(root->right);
    //updatebf(root);
    //updatebf(root->par);

    // Return the root node
    return root;
}

// Function to handle Left Right Case
struct AVLTree* LRR(struct AVLTree* root)
{
    root->left = RRR(root->left);
    return LLR(root);
}

// Function to handle right left case
struct AVLTree* RLR(struct AVLTree* root)
{
    root->right = LLR(root->right);
    return RRR(root);
}

// Function to insert a node in
// the AVL tree
struct AVLTree* Insert(struct AVLTree* root,struct AVLTree* parent,char *month)
{

    if (root == NULL) {

        // Create and assign values
        // to a new node
        root = newNode(month);

        // If the root is NULL
        if (root == NULL) {
            printf("Error");
        }

        // Otherwise
        else {
            root->height = 1;
            root->left = NULL;
            root->right = NULL;
            root->par = parent;
            root->month = month;
        }
    }

    else if (root->month > month) {

        // Recur to the left subtree
        // to insert the node
        root->left = Insert(root->left,
                            root, month);

        // Store the heights of the
        // left and right subtree
        int firstheight = 0;
        int secondheight = 0;

        if (root->left != NULL)
            firstheight = root->left->height;

        if (root->right != NULL)
            secondheight = root->right->height;

        // Balance the tree if the
        // current node is not balanced
        if (abs(firstheight
                - secondheight)
            == 2) {

            if (root->left != NULL
                && month < root->left->month) {

                // Left Left Case
                root = LLR(root);
            }
            else {

                // Left Right Case
                root = LRR(root);
            }
        }
    }

    else if (root->month <  month) {

        // Recur to the right subtree
        // to insert the node
        root->right = Insert(root->right,
                             root, month);

        // Store the heights of the
        // left and right subtree
        int firstheight = 0;
        int secondheight = 0;

        if (root->left != NULL)
            firstheight
                = root->left->height;

        if (root->right != NULL)
            secondheight = root->right->height;

        // Balance the tree if the
        // current node is not balanced
        if (abs(firstheight - secondheight) == 2) {
            if (root->right != NULL
                && month < root->right->month) {

                // Right Left Case
                root = RLR(root);
            }
            else {

                // Right Right Case
                root = RRR(root);
            }
        }
    }

    // Case when given key is already
    // in the tree
    else {
    }

    // Update the height of the
    // root node
    Updateheight(root);
    //updatebf(root);

    // Return the root node
    return root;
}

/*int calcbf(struct AVLTree *root){

}*/
// Function to print the preorder
// traversal of the AVL tree
void printpreorder(struct AVLTree* root)
{
    // Print the node's value along
    // with its parent value
    printf("Node: %s ", root->month);
    printf(",Balance Factor %d: ", getBalanceFactor(root));
    //printf("bf %d", root->bf);
    if (root->par != NULL)
        printf(",Parent Node: %s \n", root->par->month );
    else
        printf(",Parent Node: NULL\n" );


    // Recur to the left subtree
    if (root->left != NULL) {
        printpreorder(root->left);
    }

    // Recur to the right subtree
    if (root->right != NULL) {
        printpreorder(root->right);
    }
}
// Function to balance the tree after
// deletion of a node
struct AVLTree* Balance(struct AVLTree* root)
{
    // Store the current height of
    // the left and right subtree
    int firstheight = 0;
    int secondheight = 0;

    if (root->left != NULL)
        firstheight = root->left->height;

    if (root->right != NULL)
        secondheight = root->right->height;

    // If current node is not balanced
    if (abs(firstheight - secondheight) == 2) {
        if (firstheight < secondheight) {

            // Store the height of the
            // left and right subtree
            // of the current node's
            // right subtree
            int rightheight1 = 0;
            int rightheight2 = 0;
            if (root->right->right != NULL)
                rightheight2 = root->right->right->height;

            if (root->right->left != NULL)
                rightheight1 = root->right->left->height;

            if (rightheight1 > rightheight2) {

                // Right Left Case
                root = RLR(root);
            }
            else {

                // Right Right Case
                root = RRR(root);
            }
        }
        else {

            // Store the height of the
            // left and right subtree
            // of the current node's
            // left subtree
            int leftheight1 = 0;
            int leftheight2 = 0;
            if (root->left->right != NULL)
                leftheight2 = root->left->right->height;

            if (root->left->left != NULL)
                leftheight1 = root->left->left->height;

            if (leftheight1 > leftheight2) {

                // Left Left Case
                root = LLR(root);
            }
            else {

                // Left Right Case
                root = LRR(root);
            }
        }
    }

    // Return the root node
    return root;
}


struct AVLTree* Delete(struct AVLTree* root,char *month)
{
    if (root != NULL) {

        // If the node is found
        if (root->month == month) {

            // Replace root with its
            // left child
            if (root->right == NULL
                && root->left != NULL) {
                if (root->par != NULL) {
                    if (root->par->month
                        < root->month)
                        root->par->right = root->left;
                    else
                        root->par->left = root->left;

                    // Update the height
                    // of root's parent
                    Updateheight(root->par);
                }

                root->left->par = root->par;

                // Balance the node
                // after deletion
                root->left = Balance(
                    root->left);

                return root->left;
            }

            // Replace root with its
            // right child
            else if (root->left == NULL
                     && root->right != NULL) {
                if (root->par != NULL) {
                    if (root->par->month
                        < root->month)
                        root->par->right = root->right;
                    else
                        root->par->left = root->right;

                    // Update the height
                    // of the root's parent
                    Updateheight(root->par);
                }

                root->right->par = root->par;

                // Balance the node after
                // deletion
                root->right = Balance(root->right);
                return root->right;
            }

            // Remove the references of
            // the current node
            else if (root->left == NULL
                     && root->right == NULL) {
                if (root->par->month < root->month) {
                    root->par->right = NULL;
                }
                else {
                    root->par->left = NULL;
                }

                if (root->par != NULL)
                    Updateheight(root->par);

                root = NULL;
                return NULL;
            }

            // Otherwise, replace the
            // current node with its
            // successor and then
            // recursively call Delete()
            else {
                struct AVLTree* temp = root;
                temp = temp->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }

                char* val = temp->month;

                root->right
                    = Delete(root->right, temp->month);

                root->month = val;

                // Balance the node
                // after deletion
                root = Balance(root);
            }
        }

        // Recur to the right subtree to
        // delete the current node
        else if (root->month < month) {
            root->right = Delete(root->right, month);

            root = Balance(root);
        }

        // Recur into the right subtree
        // to delete the current node
        else if (root->month > month) {
            root->left = Delete(root->left, month);

            root = Balance(root);
        }

        // Update height of the root
        if (root != NULL) {
            Updateheight(root);
        }
    }

    // Handle the case when the key to be
    // deleted could not be found
    else {
        printf("Key to be deleted is not found\n");
    }

    // Return the root node
    return root;
}
void deleteTree(struct AVLTree* node)
{
    if (node == NULL) return;

    deleteTree(node->left);
    deleteTree(node->right);

    printf("\nDeleting node: %s", node->month);
    free(node);
}
