/* * * * * * *
 * Module for creating and manipulating singly-linked queues of integers
 *
 * by Raisa Litchfield <830782>
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h" // credits to Matt Farrugia <matt.farrugia@unimelb.edu.au>

// create a new queue and return a pointer to it
List *new_queue();

// destroy a queue and free its memory
void free_queue(List *queue);

// enqueue an element (adds to end of queue)
// this operation is O(1)
void queue_enqueue(List *queue, int data);

// dequeue and return an element (removes from front of queue)
// this operation is O(1)
int queue_dequeue(List *queue);

// return the number of elements contained in a queue
int queue_size(List *queue);

// returns whether the queue contains no elements (true) or some elements (false)
bool queue_is_empty(List *queue);

#endif
