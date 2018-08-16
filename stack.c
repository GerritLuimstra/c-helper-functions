/*
 * Extremely simple implementation of a stack
 * In it's current state, it only works with integers but this can be easily tweaked.
 */

#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1

// Change this to the required type
#define stack_type int

typedef struct StackNode {
    stack_type value;
    struct StackNode* prev;
    struct StackNode* next;
} StackNode;


// Creates a new stack and returns pointer to the first element
StackNode* initStack ( stack_type value ) {
    StackNode* node = malloc(sizeof(struct StackNode));
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Attempts to push a new node to the stack and returns a pointer to this node
StackNode* st_push ( StackNode* tail, stack_type value ) {
    if (tail == NULL) return NULL;

    StackNode* new = malloc(sizeof(struct StackNode));
    new->value = value;
    new->prev = tail;
    new->next = NULL;

    return new;
}

// Attempt to 'destroy' a stack and clearing it's memory used
void st_destroy ( StackNode* tail ) {
    while(tail->prev != NULL){
        free(tail);
        tail = tail->prev;
    }
}

// Pops an element off the stack and returns it's VALUE
int st_pop ( StackNode* tail ) {
    stack_type value = tail->value;

    // To 'rewire' the stack, we need to update the reference of the element before the tail to NULL
    StackNode* beforeTail = tail->prev;
    if (beforeTail != NULL){
        beforeTail->next = NULL;
    }

    free(tail);

    return value;
}

// Save a reference to the tail of the stack for ease
StackNode* tail = NULL;

int main(){
    // Create a simple stack and save a reference to the tail of the stack
    printf("%s\n", "Adding 1 to the stack.");
    tail = initStack(1);
    printf("%s\n", "Adding 2 to the stack.");
    tail = st_push(tail, 2);
    printf("%s\n", "Adding 3 to the stack.");
    tail = st_push(tail, 3);

    StackNode* theTail = tail;
    while(true){
        stack_type value = st_pop(theTail);
        printf("Popped %d off the stack.\n", value);
        if(theTail->prev == NULL) break;
        theTail = theTail->prev;
    }

    // temporary statement right now
    st_destroy(tail);
}
