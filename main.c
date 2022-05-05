#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
int main()
{
    struct AVLTree* root;
    root = NULL;
    //int i;
    //char c;
    // Function Call to insert nodes
    root = Insert(root, NULL, "June");
    root = Insert(root, NULL, "Dec");
    root = Insert(root, NULL, "Oct");
    root = Insert(root, NULL, "July");
    //root = Insert(root, NULL, "Nov");
    root = Insert(root, NULL, "August");
    //printpreorder(root);
    //int choice;
    //int cont = 1;
   /* while(cont){
        printf("\nEnter your choice:\n ");
        printf("\n1: Insert\n");
        printf("2:Delete\n ");
        printf("3:Traverse\n");
        printf("4:Destroy tree\n");
        printf("5: Quit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Enter the month you want to add: \n");
                    //char m = (char)malloc(sizeof(char));
                    scanf("%s",&c);
                    Insert(root,NULL,&c);
                    printf("Inserted element\n");
                    break;
            case 2: printf("Enter the month you want to remove: \n");
                    //char n = (char)malloc(sizeof(char));
                    scanf("%s",&c);
                    Delete(root, &c);
                    break;
            case 3: printpreorder(root);
                    break;
            case 4: printf("Deleting tree\n");
                    deleteTree(root);
                    break;
            case 5: cont = 0;
                    break;
            default: break;
        }
    }*/
    // Function call to print the tree
    printf("Before Deletion:\n");
    printpreorder(root);
    root = Delete(root, "August");
    printf("After Deletion:\n");
    printpreorder(root);

    printf("Deleting Tree:");
    deleteTree(root);

}

