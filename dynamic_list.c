/** @file   dynamic_list.c
 *  @brief  An implementation of a dynamic list of integers using arrays in C.
 *  @author Mustafa Siddiqui
 *  @date   01/06/2020
 */

#include <stdio.h>
#include <stdlib.h>

/* Updated as list expands or shrinks */
volatile int MAX_SIZE = 5;

/*
__________________________________________________________________

                        FUNCTION DECLARATIONS
__________________________________________________________________

*/

/* 
    ** The following is done for experimental purposes. It is not recommended to do so. **
    Use insertElement() with either 3 or 4 arguments.
    The following has the same result as if the function was overloaded. (not allowed in C)
    insertElement is actually a macro with expands to the functions insertElement3 or insertElement4
    depending on the number of arguments passed to it.
    If an element needs to be inserted at a specific position, include the index in arguments as well.
    Otherwise, the element would be added at the end of the list.
*/
#define NARGS(...) NARGS_(__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define NARGS_(_5, _4, _3, _2, _1, N, ...) N

#define CONC(A, B) CONC_(A, B)
#define CONC_(A, B) A##B

#define insertElement(...) CONC(insertElement, NARGS(__VA_ARGS__))(__VA_ARGS__)

void insertElement3(int* list, int value, int* end);
int insertElement4(int* list, int value, int index, int* end);

/*
    Allocate memory for and initialize the list with 0s.
    'end' keeps track of the current last element of the list.
*/
int* initializeList(int numElements, int* end);

/*
    Print all elements in the list.
*/
void printList(int* list, int* end);

/*
    Print element at a specific position to console.
*/
void displayElement(int* list, int index, int* end);

/*
    Find number of elements in the list.
    Subsequently, 'end' denotes (length of list - 1).
*/
int lengthOfList(int* list, int* end);

/*
    Delete element at a specific position from list.
*/
void deleteElement(int* list, int index, int *end);

/*
    Delete the whole list by freeing memory.
*/
void deleteList(int* list);

/*
__________________________________________________________________

                                MAIN
__________________________________________________________________

*/
int main(void) {

    // test the list implementation
    #ifdef TEST
        int end = 0;
        int* dynamicList = initializeList(MAX_SIZE, &end);

        for (int j = 0; j < 20; j++) {
            insertElement(dynamicList, (j+1), &end);
        }
        printList(dynamicList, &end);
        printf("Length of list: %d\n", lengthOfList(dynamicList, &end));

        insertElement(dynamicList, 99, 4, &end);
        printList(dynamicList, &end);
        printf("Length of list: %d\n", lengthOfList(dynamicList, &end));

        deleteElement(dynamicList, 4, &end);
        printList(dynamicList, &end);
        printf("Length of list: %d\n", lengthOfList(dynamicList, &end));

        deleteList(dynamicList);
    #endif

    return 0;
}

/*
__________________________________________________________________

                        FUNCTION DEFINITIONS
__________________________________________________________________

*/

/* Initialize list and 'end' */
int* initializeList(int numElements, int* end) {
    // allocate memory for list
    int* dynamicList = (int*)malloc(numElements * sizeof(int));
    if (dynamicList == NULL) {
        return NULL;
    }

    // initialize to zero
    for (int i = 0; i < numElements; i++) {
        dynamicList[i] = 0;
    }

    // indicates list is empty
    *end = -1;

    return dynamicList;
}

/* Insert element at end of list */
void insertElement3(int* list, int value, int* end) {
    // expand list if full
    if (*end == MAX_SIZE) {
        MAX_SIZE *= 2;
        list = realloc(list, MAX_SIZE* sizeof(int));
    }

    // if list not empty, insert at end
    if (*end != -1) {
        list[*end + 1] = value;
    }
    // if list empty, insert at start
    else {
        list[0] = value;
    }
    (*end)++;
}

/* Insert element at a specific index */
int insertElement4(int* list, int value, int index, int* end) {
    // expand list if full
    if (*end == MAX_SIZE) {
        MAX_SIZE *= 2;
        list = realloc(list, MAX_SIZE* sizeof(int));
    }

    // if list not empty, shift elements after and including index down
    if (*end != -1) {
        for (int i = *end; i >= index; i--) {
            list[i + 1] = list[i];
        }
        (*end)++;
        list[index] = value;
        return 1;
    }
    // return 0 if list empty
    else {
        return 0;
    }
}

/* Print whole list on a single line */
void printList(int* list, int* end) {
    for (int i = 0; i < *end; i++) {
        printf("%d ", list[i]);
    }
    putc('\n', stdout);
}

/* Print an element at a specific index */
void displayElement(int* list, int index, int* end) {
    if (index > *end) {
        printf("List is empty at index %d.\n", index);
    }
    else {
        printf("%d\n", list[index]);
    }
}

/* Return the number of elements in the list */
int lengthOfList(int* list, int* end) {
    return (*end + 1);
}

/* Remove element from a specific index from the list */
void deleteElement(int* list, int index, int* end) {
    // reduce size if appropriate
    if (*end < (MAX_SIZE / 2)) {
        MAX_SIZE /= 2;
        list = realloc(list, MAX_SIZE * sizeof(int));
    }

    if (index > *end) {
        printf("No element at index %d.\n", index);
    }
    // shift elements after index up
    else {
        for (int i = index; i <= *end; i++) {
            list[i] = list[i + 1];
        }
        (*end)--;
    }
}

/* Free the allocated memory for the list */
void deleteList(int* list) {
    free(list);
}