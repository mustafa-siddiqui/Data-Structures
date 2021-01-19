/** @file   circular_buffer.c
 *  @brief  An implementation of a circular buffer used to store 
 *          integers in C.
 *  @author Mustafa Siddiqui
 *  @date   01/19/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BUFFER_LENGTH (10)

/* Struct to hold circular buffer */
struct circBuff {
    int length;
    int readIndex;
    int writeIndex;
    int* values;
} typedef circBuff;

/*
__________________________________________________________________

                        FUNCTION DECLARATIONS
__________________________________________________________________

*/

/*
    Initialize buffer with '0' values. Sets the indexes to 0.
*/
void initializeBuff(circBuff* buffer, int length);

/*
    Write integer value at the next available index of the 
    circular buffer. If buffer is full, value will not be
    written to the buffer.
*/
void writeValue(circBuff* buffer, int value);

/*
    Return value from the last populated index in the buffer.
    Sebsequently, the value returned is no longer stored in
    the buffer. If the buffer is empty, returns 0.
*/
int popValue(circBuff* buffer);

/*
    Free the allocated memory for the circular buffer. Frees
    the integer array and the buffer itself.
*/
void freeBuffer(circBuff* buffer);

/*
__________________________________________________________________

                                MAIN
__________________________________________________________________

*/

int main(void) {
    // allocate memory for buffer
    circBuff* buffer = (circBuff*) malloc(sizeof(circBuff));
    assert(buffer);

    // intialize buffer & its elements
    initializeBuff(buffer, MAX_BUFFER_LENGTH);

    // populate buffer till max length
    for (int i = 0; i < (MAX_BUFFER_LENGTH + 1); i++) {
        writeValue(buffer, (i + 1));
    }
    // pop values from buffer
    for (int i = 0; i < (MAX_BUFFER_LENGTH + 1); i++) {
        printf("%d\n", popValue(buffer));
    }

    // free allocated memory
    freeBuffer(buffer);

    return 0;
}

/*
__________________________________________________________________

                        FUNCTION DEFINITIONS
__________________________________________________________________

*/

void initializeBuff(circBuff* buffer, int length) {
    // allocate memory for integer array
    int* temp = (int*) malloc(length * sizeof(int));
    assert(temp);
    buffer->values = temp;

    // initialize array to 0
    for (int i = 0; i < length; i++) {
        buffer->values[i] = 0;
    }

    // initialize index values
    buffer->readIndex = 0;
    buffer->writeIndex = 0;
    buffer->length = 0;
}

void writeValue(circBuff* buffer, int value) {
    // return if buffer is full
    if (buffer->length == MAX_BUFFER_LENGTH) {
        printf("Buffer is full. Cannot write value '%d'.\n", value);
        return;
    }

    // insert value
    buffer->values[buffer->writeIndex] = value;
    buffer->writeIndex++;
    buffer->length++;

    // wrap around if buffer is full
    if (buffer->writeIndex == MAX_BUFFER_LENGTH) {
        buffer->writeIndex = 0;
    }
}

int popValue(circBuff* buffer) {
    // return if buffer is empty
    if (buffer->length == 0) {
        printf("Circular buffer is empty. Cannot read value.\n");
        return 0;
    }

    // update index values and reset value
    int temp = buffer->values[buffer->readIndex];
    buffer->values[buffer->readIndex] = 0;
    buffer->length--;
    buffer->readIndex++;

    return temp;
}

void freeBuffer(circBuff* buffer) {
    // free integer array and the buffer struct
    free(buffer->values);
    free(buffer);
}