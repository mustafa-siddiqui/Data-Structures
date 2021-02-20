/** @file   linked_list.c
 *  @brief  An implementation of a linked list of integers in C.
 *  @author Mustafa Siddiqui
 *  @date   01/13/2020
 */

#include <stdio.h>
#include <stdlib.h>

struct linkedListNode {
    int value;
    struct linkedListNode* next;
} typedef Node;

/*
__________________________________________________________________

                        FUNCTION DECLARATIONS
__________________________________________________________________

*/

/* 
    Append value to the end of the list.
*/
Node* append(Node* head, int value);

/*
    Insert value after some value/element in the list.
    'valueBeforeInsert' is the value in the list after which the new 
    value will be inserted.
*/
void insertAfter(Node* head, int valueBeforeInsert, int insertValue);

/*
    Insert value before some value/element in the list.
    'valueAfterInsert' is the value in the list before which the new
    value will be inserted.
    Returns Node* since the head of the list can be changed.
*/
Node* insertBefore(Node* head, int valueAfterInsert, int insertValue);

/*
    Delete element from list.
*/
void delete(Node* head, int valueToDelete);

/*
    Search for value in the list.
    Returns '-1' if value not found & the position/index of the value 
    in the list if found.
*/
int search(Node* head, int valueToSearch);

/*
    Reverse list by editing the passed list instead of creating a new
    one. Returns the head of the reversed list.
*/
Node* reverseList(Node* head);

/*
    Reverse the list recursively.
    Returns the updated head of the list.
*/
Node* reverseListRecursively(Node* curr, Node* prev);

/*
    Print all elements in the list.
*/
void printList(Node* head);

/*
    Print all elements in the list in reverse.
    Recursive function.
*/
void printListReverse(Node* head);

/*
    Free memory for all elements in the list.
*/
void freeList(Node* head);

/*
__________________________________________________________________

                                MAIN
__________________________________________________________________

*/

int main(void) {

    Node* head = (Node*) malloc(sizeof(Node));
    head = NULL;

    // populate list and print
    for (int i = 0; i < 10; i++) {
        head = append(head, (i + 1));
    }
    printList(head);

    // insert '99' into list after the value '5'
    insertAfter(head, 5, 99);
    printList(head);

    // insert '101' into list before the value '99'
    head = insertBefore(head, 1, 101);
    printList(head);

    // delete '99' from the list
    delete(head, 99);
    printList(head);

    // print linked list in reverse without reversing it
    printf("List printed in reverse:\n");
    printListReverse(head);
    printf("\n");

    // reverse the list iteratively
    printf("Reversed list:\n");
    head = reverseList(head);
    printList(head);

    // reverse the list recursively
    head = reverseListRecursively(head, NULL);
    printList(head);

    // search '10' in list
    int valueToSearch = 1000;
    printf("'%d' at position: %d\n", valueToSearch, search(head, valueToSearch));

    // free memory for all list nodes
    freeList(head);

    return 0;
}

/*
__________________________________________________________________

                        FUNCTION DEFINITIONS
__________________________________________________________________

*/

/* Append at end of list */
Node* append(Node* head, int value) {
    // create new node
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    // if list empty, new node will become head
    if (head == NULL) {
        return newNode;
    }

    // iterate to the end of the list
    Node* currentNode = head;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    // append new node
    currentNode->next = newNode;

    return head;
}

/* Insert value into list after some value. */
void insertAfter(Node* head, int valueBeforeInsert, int insertValue) {
    Node* currentNode = head;

    // iterate over list until value reached
    while (currentNode->value != valueBeforeInsert) {
        currentNode = currentNode->next;

        // return if value not in list
        if (currentNode == NULL) {
            printf("'%d' not in list.\n", valueBeforeInsert);
            return;
        }
    }

    // create node to be inserted
    Node* insertNode = (Node*) malloc(sizeof(Node));
    insertNode->value = insertValue;
    insertNode->next = currentNode->next;

    // make current node point to node to be inserted (which points to the next node)
    currentNode->next = insertNode;
}

/* Insert value into list before some value. */
Node* insertBefore(Node* head, int valueAfterInsert, int insertValue) {
    Node* currentNode = head;
    Node* previousNode = NULL;
    
    // iterate over loop until value reached
    while (currentNode->value != valueAfterInsert) {
        previousNode = currentNode;
        currentNode = currentNode->next;

        // return if value not in list
        if (currentNode == NULL) {
            printf("'%d' not in list.\n", valueAfterInsert);
            return head;
        }
    }

    // create node to be inserted
    Node* insertNode = (Node*) malloc(sizeof(Node));
    insertNode->value = insertValue;
    insertNode->next = currentNode;

    // if value is to be inserted before head
    // currentNode will be the same as head in this case
    if (head->value == valueAfterInsert) {
        head = insertNode;
    }
    else {
        // make node before search value node point to node to be inserted (which points to the next node)
        // previousNode will not be NULL since have iterated over list
        previousNode->next = insertNode;
    }

    return head;
}

/* Delete value from list. */
void delete(Node* head, int valueToDelete) {
    Node* currentNode = head;
    Node* previousNode = NULL;

    // iterate over list until value to be deleted is reached
    while (currentNode->value != valueToDelete) {
        previousNode = currentNode;
        currentNode = currentNode->next;

        // return if value not in list
        if (currentNode == NULL) {
            printf("'%d' not in list.\n", valueToDelete);
            return;
        }
    }

    // connect previous and after nodes
    previousNode->next = currentNode->next;

    // free node with value to be deleted
    free(currentNode);
}

/* Search value in list. */
int search(Node* head, int valueToSearch) {
    Node* currentNode = head;

    // iterate over list until value is found or till end of list while
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

/* Reverse list. */
Node* reverseList(Node* head) {
    if ((head == NULL) || head->next == NULL) {
        return head;
    }

    Node* currentNode = head;
    Node* next = NULL;
    Node* prev = NULL;
    while (currentNode != NULL) {
        next = currentNode->next;
        currentNode->next = prev;

        prev = currentNode;
        currentNode = next;
    }

    head = prev;

    return head;
}

/* Reverse list recursively. */
Node* reverseListRecursively(Node* curr, Node* prev) {
    Node* head = curr;
    
    // traverse recursively to end of list while
    // keeping track of current and previous nodes
    if (curr->next != NULL)
        head = reverseListRecursively(curr->next, curr);

    // update head when end of list reached
    if (curr->next == NULL)
        head = curr;

    // update the next nodes
    curr->next = prev;
    return head;
}

/* Print list. */
void printList(Node* head) {
    Node* currenNode = head;

    // iterate over list and print values
    while (currenNode != NULL) {
        printf("%d ", currenNode->value);
        currenNode = currenNode->next;
    }
    printf("\n");
}

/* Print list in reverse. */
void printListReverse(Node* head) {
    // base case
    if (head == NULL) {
        return;
    }
    
    // recursive call to next node
    printListReverse(head->next);

    // print data
    printf("%d ", head->value);
}

/* Free up memory allocated for list. */
void freeList(Node* head) {
    Node* currentNode = head;
    Node* previousNode = NULL;

    // iterate over the list and free nodes as we go
    while (currentNode != NULL) {
        previousNode = currentNode;
        currentNode = currentNode->next;

        free(previousNode);
    }
}
