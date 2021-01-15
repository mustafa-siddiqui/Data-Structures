/** @file   stack.c
 *  @brief  An implementation of a stack of integers in C. The data
 *          structure follows the LIFO (Last In First Out) principle. 
 *  @author Mustafa Siddiqui
 *  @date   01/13/2020
 */

#include <stdio.h>
#include <stdlib.h>

struct stackNode {
    int value;
    struct stackNode* next;
} typedef Node;

/*
__________________________________________________________________

                        FUNCTION DECLARATIONS
__________________________________________________________________

*/

/*
    Add a value to the top of stack.
    Returns pointer to top of stack.
*/
Node* push(Node* top, int value);

/*
    Delete a value from the top of stack.
    Returns pointer to top of stack.
*/
Node* pop(Node* top);

/*
    Search a value in the stack.
    Returns the position/index of the value in the stack if
    value is present in the stack and '-1' if value searched
    is not in stack.
*/
int search(Node* top, int valueToSearch);

/*
    Print all elements in the stack.
*/
void printStack(Node* top);

/*
    Free up allocated memory for all elements in the stack.
*/
void freeStack(Node* top);

/*
__________________________________________________________________

                                MAIN
__________________________________________________________________

*/

int main(void) {
    Node* top = (Node*) malloc(sizeof(Node));
    top = NULL;

    // populate stack with values and print
    for (int i = 0; i < 10; i++) {
        top = push(top, (i + 1));
    }
    printStack(top);

    // delete first 5 values from stack
    for (int j = 0; j < 5; j++) {
        top = pop(top);
    }
    printStack(top);

    // search for num in stack
    int num = 1;
    printf("'%d' at position %d.\n", num, search(top, num));

    // free up allocated memory
    freeStack(top);

    return 0;
}

/*
__________________________________________________________________

                        FUNCTION DEFINITIONS
__________________________________________________________________

*/

/* Push node to top of stack */
Node* push(Node* top, int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = top;

    return newNode;
}

/* Delete node from top of stack. */
Node* pop(Node* top) {
    Node* temp = top;
    Node* newTop = temp->next;

    // free node
    free(temp);

    return newTop;
}

/* Search value in stack. */
int search(Node* top, int valueToSearch) {
    Node* currentNode = top;

    // iterate through stack until value is found or till end of list while
    // keeping track of how many iterations made
    int index = 0;
    while (currentNode->value != valueToSearch) {
        currentNode = currentNode->next;
        index++;

        if (currentNode == NULL) {
            // value not found, return -1
            return -1;
        }
    }

    return index;
}

/* Print elements stored in stack. */
void printStack(Node* top) {
    Node* currentNode = top;

    // iterate through stack
    while (currentNode->next != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }

    // print last element in stack
    printf("%d\n", currentNode->value);
}

/* Free up allocated memory. */
void freeStack(Node* top) {
    Node* currentNode = top;
    Node* previousNode = NULL;

    // iterate through stack and free up nodes as we go
    while (currentNode != NULL) {
        previousNode = currentNode;
        currentNode = currentNode->next;

        free(previousNode);
    }
}
