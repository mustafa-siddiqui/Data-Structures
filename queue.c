/** @file   queue.c
 *  @brief  An implementation of a queue of integers in C. The data
 *          structure follows the FIFO (First In First Out) principle. 
 *  @author Mustafa Siddiqui
 *  @date   01/13/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct queueNode {
    int value;
    struct queueNode* next;
} typedef Node;

/* Struct to hold head and tail nodes for queue. */
struct queue {
    Node* head;
    Node* tail;
} typedef Queue;

/*
__________________________________________________________________

                        FUNCTION DECLARATIONS
__________________________________________________________________

*/

/*
    Allocate memory for queue and initialize to NULL.
*/
Queue* createQueue(void);

/*
    Perform enqueue operation. Pushes value to the end of the queue.
*/
void enqueue(Queue* queue, int value);

/*
    Perform dequeue operation. Pops element from the head of the queue
    and returns the value popped.
*/
int dequeue(Queue* queue);

/*
    Search a value in queue.
    Returns the position/index of the value in the queue if value is 
    present and '-1' if value searched is not in queue.
*/
int search(Queue* queue, int valueToSearch);

/*
    Print all elements in the queue.
*/
void printQueue(Queue* queue);

/*
    Free up allocated memory for all elements in the queue.
*/
void freeQueue(Queue* queue);

/*
__________________________________________________________________

                                MAIN
__________________________________________________________________

*/

int main(void) {
    Queue* queue = createQueue();

    // populate queue and print
    for (int i = 0; i < 10; i++) {
        enqueue(queue, (i + 1));
    }
    printQueue(queue);

    // pop 5 elements from queue
    for (int j = 0; j < 5; j++) {
        printf("Deleted %d\n", dequeue(queue));
    }
    printQueue(queue);

    // search num in queue
    int num = 10;
    printf("%d found at position %d.\n", num, search(queue, num));

    // free up allocated memory
    freeQueue(queue);

    return 0;
}

/*
__________________________________________________________________

                        FUNCTION DEFINITIONS
__________________________________________________________________

*/

/* Create queue and initialize. */
Queue* createQueue(void) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    assert(queue);

    // intialize to NULL to denote empty queue
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

/* Push element to queue. */
void enqueue(Queue* queue, int value) {
    // create new node to be inserted at tail
    Node* newNode = (Node*) malloc(sizeof(Node));
    assert(newNode);

    newNode->value = value;
    newNode->next = NULL;

    // if queue empty, insert at head
    if (queue->head == NULL) {
        queue->head = newNode;
    }
    // if queue not empty, insert at tail
    else {
        // since the head and tail are the same when there is 1 element in queue
        // this will update 'head->next' also (when the second element is inserted)
        queue->tail->next = newNode;
    }

    // update tail pointer
    queue->tail = newNode;
}

/* Pop queue element. */
int dequeue(Queue* queue) {
    if (queue->head == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }

    // store current head in a temporary variable & get value
    Node* temp;
    temp = queue->head;
    int value = temp->value;

    // update head of queue
    queue->head = queue->head->next;

    // free memory allocated for deleted element
    free(temp);

    return value;
}

/* Search value in queue. */
int search(Queue* queue, int valueToSearch) {
    Node* currentNode = queue->head;

    // iterate through queue until value is found or till end of queue
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

/* Print list. */
void printQueue(Queue* queue) {
    Node* currenNode = queue->head;
    if (currenNode == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    // iterate over list and print values
    while (currenNode->next != NULL) {
        printf("%d ", currenNode->value);
        currenNode = currenNode->next;
    }

    // print last element in the list
    printf("%d\n", currenNode->value);
}

/* Free up allocated memory. */
void freeQueue(Queue* queue) {
    Node* currentNode = queue->head;

    // iterate over queue freeing nodes as we go using dequeue()
    while (currentNode != NULL) {
        currentNode = currentNode->next;
        dequeue(queue);
    }
}