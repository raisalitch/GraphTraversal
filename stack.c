/* * * * * * *
 * Module for creating and manipulating singly-linked stacks of integers
 *
 * by Raisa Litchfield <830782>
 */

#include <stdlib.h>
#include <assert.h>
#include "stack.h"

// create a new stack and reutrn a pointer to it
List *new_stack() {
    return new_list();
}

// destroy a stack and free its memory
void free_stack(List *stack) {
    free_list(stack);
}

// push an element to the stack (adds to front of stack)
// this operation is O(1)
void stack_push(List *stack, int data) {
    list_add_start(stack, data);
}

// pop and return an element from the stack (removes from front of stack)
// this operation is O(1)
// error if the stack is empty (so first ensure stack_size() > 0)
int stack_pop(List *stack) {
    return list_remove_start(stack);
}

// return the number of elements contained in a stack
int stack_size(List *stack) {
    return list_size(stack);
}

// returns whether the stack contains no elements (true) or some elements (false)
bool stack_is_empty(List *stack) {
    return list_is_empty(stack);
}
