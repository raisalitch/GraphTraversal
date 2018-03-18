/* * * * * * *
 * Module for creating and manipulating singly-linked stacks of integers
 *
 * by Raisa Litchfield <830782>
 */

#ifndef STACK_H
#define STACK_H

#include "list.h" // credits to Matt Farrugia <matt.farrugia@unimelb.edu.au>

// create a new stack and return a pointer to it
List *new_stack();

// destroy a queue and free its memory
void free_stack(List *stack);

// push an element to the stack (adds to front of stack)
// this operation is O(1)
void stack_push(List *stack, int data);

// pop and return an element from the stack (removes from front of stack)
// this operation is O(1)
int stack_pop(List *stack);

// return the number of elements contained in a stack
int stack_size(List *stack);

// returns whether the stack contains no elements (true) or some elements (false)
bool stack_is_empty(List *stack);

#endif
