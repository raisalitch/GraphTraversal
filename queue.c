/* * * * * * *
 * Module for creating and manipulating singly-linked queues of integers
 *
 * by Raisa Litchfield <830782>
 */

#include <stdlib.h>
#include <assert.h>
#include "queue.h"

// create a new queue and reutrn a pointer to it
List *new_queue() {
    return new_list();
}

// destroy a queue and free its memory
void free_queue(List *queue) {
    free_list(queue);
}

// enqueue an element (adds to end of queue)
// this operation is O(1)
void queue_enqueue(List *queue, int data) {
    list_add_end(queue, data);
}

// dequeue and return an element (removes from front of queue)
// this operation is O(1)
// error if the queue is empty (so first ensure queue_size() > 0)
int queue_dequeue(List *queue) {
    return list_remove_start(queue);
}

// return the number of elements contained in a queue
int queue_size(List *queue) {
    return list_size(queue);
}

// returns whether the queue contains no elements (true) or some elements (false)
bool queue_is_empty(List *queue) {
    return list_is_empty(queue);
}
