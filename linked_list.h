#ifndef LINKED_LIST_H

#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
//in this linked listed some of the function use pointers to pointers.
//this is for changing pointers that points nodes
typedef enum {
    LL_OK,
    LL_ERR_ALLOC,
    LL_NODE_NOT_FOUND,
    LL_ERR_EMPTY
} LL_Status;

struct node {
    int data;
    struct node *next;
};

//function prototypes
// Initializes a linked list with data from an array
LL_Status initialize_linked_list(struct node **, int [], unsigned int );
// Prints each node by using head pointer 
void display_linked_list(struct node *);
// Adds node to beginning of the list
LL_Status add_node_to_beginning(struct node **, int);
// Adds node to end of the list
LL_Status add_node_to_end(struct node **, int);
// Adds node to before of given node by value
LL_Status add_node_before_given_node(struct node **, int, int);
// Adds node to after of given node by value
LL_Status add_node_after_given_node(struct node **, int, int);
// Deletes the first node. If list is empty it returns empty status
LL_Status delete_first_node(struct node **);
// Deletes last node of list. If list is empty it returns empty status
LL_Status delete_last_node(struct node **);
// Deletes given node of list. If list is empty it returns empty status
LL_Status delete_given_node(struct node **, int);
// Searchs list to find the given node by value.
// Returns a pointer to the node if it founds it
// Returns NULL if it didn't found it.
struct node *search_node(struct node *, int);
// Sorts list by merge sort algortihm.
// This function returns a new head pointer, which must
// be assigned back to the original list head by the caller.
struct node *merge_sort_linked_list(struct node *);
//deletes linked list
LL_Status delete_linked_list(struct node **);

#endif