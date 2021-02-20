/** @file   binary_tree.c
 *  @brief  Binary tree structure with a struct emulating an object with
 *          methods by employing function pointers as elements.
 *          ** All methods of tree traversal are recursive. **
 *  @author Mustafa Siddiqui
 *  @date   02/19/2021
 */

#include <stdio.h>
#include <stdlib.h>         // malloc()

/* 
    Struct definition for tree node. Contains a function pointer which
    emulates the functionality of an object in OOP.
    Holds
*/
struct Node {
    // basic binary tree elements
    int value;
    struct Node* left;
    struct Node* right;

    // function pointers emulating methods of an object for struct
    struct Node* (*addNode)(struct Node*, int);
    void (*printAscending)(struct Node*);
    void (*printDescending)(struct Node*);
    void (*freeTree)(struct Node*);

} typedef treeNode;

/*
__________________________________________________________________

                        FUNCTION DECLARATIONS
__________________________________________________________________

*/

/*
    Create and initialize node with appropriate values. malloc() is not 
    to be used to create a new node as this provides the correct initial
    values for a node and assigns the function pointer to the correct 
    function.
*/
treeNode* createNode(int data);

/*
    Append node to tree in order. Adds a right child if the value to
    be added is greater than the value of the root node and adds a 
    left child if the value is lesser.
*/
treeNode* addNodeToTree(treeNode* root, int value);

/*
    Traverses through the tree until the value passed as argument is
    found or the whole tree is traversed (not all elements though due
    to the tree characteristics).
    Returns the node where the value is stored.
*/
treeNode* findValue(treeNode* root, int value);

/*
    Print tree in ascending order. Recursively traverses through the 
    tree to the left most child first for each node, printing on its
    way up to the root. 
*/
void ascending(treeNode* root);

/*
    Print tree in descending order. Recursively traverses through
    the tree to the right most child first for each node, printing
    on its way up to the root.
*/
void descending(treeNode* root);

/*
    Function to be one of the struct (binary tree) elements. Prints
    the tree on a separate line. Makes use of ascending().
*/
void printTreeAscending(treeNode* root);

/*
    Function to be one of the struct (binary tree) elements. Prints
    the tree on a separate line. Makes use of descending().
*/
void printTreeDescending(treeNode* root);

/*
    Free up allocated memory for each node in the binary tree. 
    Traverses through the tree recursively by reaching the left 
    most node first and frees up nodes one by one.
*/
void freeTree(treeNode* root);

/*
__________________________________________________________________

                                MAIN
__________________________________________________________________

*/
int main(void) {

    treeNode* binaryTree = createNode(0);

    /* create the following tree:
     *              0
     *                \ 
     *                  1
     *                    \ 
     *                      4
     *                     /  \ 
     *                    3    7
     *                        / 
     *                       5  
    */
    for (int i = 1; i < 10; i += 3) {
        binaryTree->addNode(binaryTree, i);
    }
    binaryTree->addNode(binaryTree, 3);
    binaryTree->addNode(binaryTree, 5);

    binaryTree->printAscending(binaryTree);
    binaryTree->printDescending(binaryTree);

    treeNode* node = findValue(binaryTree, 4);
    if (node)
        printf("%d\n", node->value);

    binaryTree->freeTree(binaryTree);

    return 0;
}

/*
__________________________________________________________________

                        FUNCTION DEFINITIONS
__________________________________________________________________

*/

/* Create and initialize node */
treeNode* createNode(int data) {
    treeNode* binaryNode = (treeNode*) malloc(sizeof(treeNode));
    binaryNode->value = data;
    binaryNode->left = NULL;
    binaryNode->right = NULL;
    binaryNode->addNode = addNodeToTree;
    binaryNode->printAscending = printTreeAscending;
    binaryNode->printDescending = printTreeDescending;
    binaryNode->freeTree = freeTree;

    return binaryNode;
}

/* Add node to tree */
treeNode* addNodeToTree(treeNode* root, int value) {
    // base case
    if (root == NULL)
        return createNode(value);
    
    // recursive calls according to value
    if (value > root->value)
        root->right = addNodeToTree(root->right, value);
    else if (value < root->value)
        root->left = addNodeToTree(root->left, value);

    return root;
}

/* Find value in tree */
treeNode* findValue(treeNode* root, int value) {
    // traverse until value found or end of tree
    if (root == NULL)
        return NULL;
    else if (value == root->value)
        return root;
    else if (value > root->value)
        return (findValue(root->right, value));
    else if (value < root->value)
        return (findValue(root->left, value));

    return NULL;
}

/* Print tree in ascending order */
void ascending(treeNode* root) {
    // traverse through the left tree first
    if (root->left != NULL)
        ascending(root->left);

    printf("%d ", root->value);

    // traverse through the right tree after printing
    if (root->right != NULL)
        ascending(root->right);

    return;
}

/* Struct function for tree traversal */
void printTreeAscending(treeNode* root) {
    ascending(root);
    printf("\n");
}

/* Print tree in descending order */
void descending(treeNode* root) {
    // traverse through the right tree first
    if (root->right != NULL)
        descending(root->right);

    printf("%d ", root->value);

    // traverse through the left tree after printing
    if (root->left != NULL)
        descending(root->left);

    return;
}

/* Struct function for tree traversal */
void printTreeDescending(treeNode* root) {
    descending(root);
    printf("\n");
}

/* Free up allocated memory for tree nodes */
void freeTree(treeNode* root) {
    // traverse through the tree recursively and free
    // up nodes as you go
    if (root->left != NULL)
        freeTree(root->left);

    //printf("Freeing %d\n", root->value);
    free(root);

    if (root->right != NULL)
        freeTree(root->right);

    return;
}