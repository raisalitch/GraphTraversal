/* * * * * * *
 * Module for Assignment Parts 1 to 4.
 *
 * Includes functions for Depth-First Traversal, Breadth-First Traversal,
 * Finding a Detailed Path, Finding All Paths and Finding the Shortest Path.
 *
 * by Raisa Litchfield <830782>
 */

#include <stdio.h>
#include <stdbool.h>
#include "traverse.h"
#include "list.h" // credits to Matt Farrugia <matt.farrugia@unimelb.edu.au>
#include "queue.h"
#include "stack.h"

void false_array(Graph* graph, bool array[]);
void stack_print(List* stack, Graph* graph, bool print_dist,
                 int total_distance);

void breadth_explore(Graph* graph, Vertex* vertex, int id, bool visited[],
                     List *queue);

void dfs_path(Graph* graph, int destination_id, int id, bool is_source,
              List* stack, bool visited[]);

void short_path_search(Graph* graph, int destination_id, int id,
                       bool is_source, List* distances, List* curr_distance,
                       List* stack, bool visited[], bool find_shortest,
                       int shortest_loc, int *count);
int distance_sum(List* curr_distance);

/******************************************************************************/


/* PART 1: Print vertices using depth-first search algorithm. */
void print_dfs(Graph* graph, int source_id) {
    
    // Create false visited array
    bool visited[graph->n];
    false_array(graph, visited);
    
    // Create a stack
    List* stack=new_stack();
    List* tempstack=new_stack();
    
    // Initialize the vertex id
    int id = source_id;
    Edge* curredge;
    
    stack_push(stack, id);
    
    // Iterate until stack is empty (until all vertices have been visited
    // and depth first search is finished)
    while (!stack_is_empty(stack)) {
        id = stack_pop(stack);
        
        // Vertex is unvisited
        if (!visited[id]) {
            visited[id] = true;
            printf("%s\n", graph->vertices[id]->label);
            
            curredge = graph->vertices[id]->first_edge;
            
            // Iterate through the edges of the current vertex
            while (curredge != NULL) {
                stack_push(tempstack, curredge->v);
                curredge = curredge->next_edge;
            }
            
            // Re-add to stack in correct order
            while (!stack_is_empty(tempstack)) {
                stack_push(stack, stack_pop(tempstack));
            }
        }
    }
    
    free_stack(stack);
    free_stack(tempstack);
}

/******************************************************************************/

/* PART 2: Print vertices using breadth-first search algorithm. */
void print_bfs(Graph* graph, int source_id) {
    
    // Create false visited array
    bool visited[graph->n];
    false_array(graph, visited);
    
    // Inititalize the vertex id
    int id = source_id;
    
    // Create queue and enqueue initial vertex id
    List* queue=new_queue();
    queue_enqueue(queue, id);
    
    while (!queue_is_empty(queue)) {
        id = queue_dequeue(queue);
        breadth_explore(graph, graph->vertices[id], id, visited, queue);
    }
    
    free_queue(queue);
    
}

// Prints the order in which vertices are discovered using a breadth first
// search method
void breadth_explore(Graph* graph, Vertex* vertex, int id, bool visited[],
                     List *queue) {
    // Set to visited and print
    if (!visited[id]) {
        visited[id] = true;
        printf("%s\n", vertex->label);
    }
    
    Edge* curredge = vertex->first_edge;
    
    // Iterate through all edges from current vertex
    while (curredge != NULL) {
        // Set id, enqueue, set to visited and print if unvisited
        if (!visited[curredge->v]) {
            id = curredge->v;
            queue_enqueue(queue, id);
            visited[id] = true;
            printf("%s\n", graph->vertices[id]->label);
        }
        curredge = curredge->next_edge;
    }
}

/******************************************************************************/

/* PART 3: print all paths */
void all_paths(Graph* graph, int source_id, int destination_id) {
    
    // Create zeroed visited array
    bool visited[graph->n];
    false_array(graph, visited);
    
    // Create a stack
    List* stack=new_stack();
    
    dfs_path(graph, destination_id, source_id, true, stack, visited);
    
    free_stack(stack);
}

// Finds a simple path from id to destination_id using depth first search
void dfs_path(Graph* graph, int destination_id, int id, bool is_source,
              List* stack, bool visited[]) {
    
    Edge *curredge=graph->vertices[id]->first_edge;
    
    if (is_source) {
        stack_push(stack, id);
        visited[id] = true;
    }
    
    // Iterate until the stack is empty
    while (!stack_is_empty(stack)) {
        id = curredge->v;
        
        // Vertex is unvisited
        if (!visited[id]) {
            visited[id] = true;
            stack_push(stack, id);
            
            // Destination is reached
            if (destination_id == id) {
                stack_print(stack, graph, false, 0);
                stack_pop(stack);
            }
            // Destination is not reached
            else
                dfs_path(graph, destination_id, id, false, stack, visited);
            
            visited[id] = false;
        }
        curredge = curredge->next_edge;
        if (curredge == NULL) {
            stack_pop(stack);
            break;
        }
    }
}

/******************************************************************************/

/* PART 4: print shortest path */
void shortest_path(Graph* graph, int source_id, int destination_id) {
	
    // Create false visited array
    bool visited[graph->n];
    false_array(graph, visited);
    
    // Create a stack and queue
    List* stack=new_stack();
    List* curr_distance=new_stack();
    List* distances=new_queue();
    
    short_path_search(graph, destination_id, source_id, true, distances,
                      curr_distance, stack, visited, false, 0, 0);
    
    int x, shortest=queue_dequeue(distances), shortest_loc=0, count=1;

    while (!queue_is_empty(distances)) {
        x = queue_dequeue(distances);
        if (x < shortest) {
            shortest = x;
            shortest_loc = count;
        }
        count++;
    }
    
    int i=0;
    short_path_search(graph, destination_id, source_id, true, distances,
                      curr_distance, stack, visited, true, shortest_loc, &i);
    
    free_stack(stack);
    free_stack(curr_distance);
    free_queue(distances);
}

// Stores distances of all simple paths in distances list if find_shortest
// is false. Otherwise, if find_shortest is true, iterates until the shortest
// path is reached and then prints the path and its distance.
void short_path_search(Graph* graph, int destination_id, int id,
                       bool is_source, List* distances, List* curr_distance,
                       List* stack, bool visited[], bool find_shortest,
                       int shortest_loc, int *count) {
    int total_distance=0;
    
    Edge *curredge=graph->vertices[id]->first_edge;
    
    if (is_source) {
        stack_push(stack, id);
        visited[id] = true;
    }
    
    // Iterate until the stack is empty
    while (!stack_is_empty(stack)) {
        id = curredge->v;
        
        // Vertex is unvisited
        if (!visited[id]) {
            visited[id] = true;
            stack_push(stack, id);
            stack_push(curr_distance, curredge->weight);
            
            // Destination is reached
            if (destination_id == id) {
                total_distance = distance_sum(curr_distance);
                if (find_shortest) {
                    if (*count == shortest_loc) {
                        stack_print(stack, graph, true, total_distance);
                        break;
                    }
                    *count += 1;
                }
                stack_pop(stack);
                stack_pop(curr_distance);
                queue_enqueue(distances, total_distance);
            }
            // Destination is not reached
            else
                short_path_search(graph, destination_id, id, false, distances,
                                  curr_distance, stack, visited, find_shortest,
                                  shortest_loc, count);
            
            visited[id] = false;
        }
        
        curredge = curredge->next_edge;
        if (curredge == NULL) {
            stack_pop(stack);
            if (!stack_is_empty(curr_distance))
                stack_pop(curr_distance);
            break;
        }
    }
}

// Calculates the total distance by adding all distances in curr_distance list
int distance_sum(List* curr_distance) {
    int x, sum=0;
    List* tempstack=new_stack();
    while (!stack_is_empty(curr_distance)) {
        x = stack_pop(curr_distance);
        sum += x;
        stack_push(tempstack, x);
    }
    while (!stack_is_empty(tempstack))
        stack_push(curr_distance, stack_pop(tempstack));
    
    return sum;
    
    free_stack(tempstack);
}

/******************************************************************************/

// Initializes all array values to false
void false_array(Graph* graph, bool array[]) {
    int i;
    for (i=0; i < graph->n; i++)
        array[i] = false;
}

// Prints the path stored in the stack
void stack_print(List* stack, Graph* graph, bool print_dist,
                 int total_distance) {
    int x;
    List* tempstack=new_stack();
    while (!stack_is_empty(stack))
        stack_push(tempstack, stack_pop(stack));
    
    while (stack_size(tempstack)>1) {
        x = stack_pop(tempstack);
        stack_push(stack, x);
        printf("%s, ", graph->vertices[x]->label);
    }
    
    x = stack_pop(tempstack);
    if (print_dist)
        printf("%s (%dkm)\n", graph->vertices[x]->label, total_distance);
    else
        printf("%s\n", graph->vertices[x]->label);
    stack_push(stack, x);
    
    free_stack(tempstack);
}
