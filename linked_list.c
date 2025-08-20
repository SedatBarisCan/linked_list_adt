#include <stdio.h>
#include <stdlib.h>
//in this linked listed some of the function use pointers to pointers.
//this is for changing pointers that points nodes
#include "linked_list.h"

struct node *merge_linked_list(struct node *, struct node *);

//function implementations
struct node *create_node(int data)
{
    struct node *new_node = (struct node*) malloc(sizeof(struct node));
    if (new_node == NULL) return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

LL_Status initialize_linked_list(struct node **head, int data[], unsigned int n)
{
    *head = NULL;
    if (n == 0)
        return LL_OK;
    
    *head = create_node(data[0]);
    if ((*head) == NULL) return LL_ERR_ALLOC;
        
   

    struct node *position = *head;

    for (int i = 1; i < n; i++)
    {
        struct node *new_node = create_node(data[i]);
        if (new_node == NULL) return LL_ERR_ALLOC;
        position->next = new_node;
        position = position->next;
    }
    return LL_OK;
}
void display_linked_list(struct node *head)
{
    int count = 1;
    struct node *position = head;
    while (position != NULL) 
    {        
        printf("data %d: %d\n", count, position->data);
        position = position->next;
        count++;
    }
}
LL_Status add_node_to_beginning(struct node** head, int data)
{
    //assign node to the list
    struct node *new_node = create_node(data);
    if (new_node == NULL) return LL_ERR_ALLOC;
    new_node->next = *head;
    *head = new_node;

    return LL_OK;
}
LL_Status add_node_to_end(struct node** head, int data)
{
    struct node *position, *new_node;
    if (*head == NULL)
        return add_node_to_beginning(head, data);
    position = *head;
    while (position->next != NULL)
        position = position->next;

    //assign node to the list
    new_node = create_node(data);
    if (new_node == NULL) return LL_ERR_ALLOC;

    
    position->next = new_node;
    new_node->next = NULL;

    return LL_OK;
}
LL_Status add_node_before_given_node(struct node **head, int data, int given_value)
{
    if (*head == NULL)  return  LL_ERR_EMPTY;
    struct node *position, *pre_position;

    if ((*head)->data == given_value)              // this code checks if given node is head node.
         return add_node_to_beginning(head, data); // if it is this code adds node to beginning
    
    pre_position = *head;
    position = (*head)->next;
    while (position->next != NULL && position->data != given_value)
    {
        pre_position = pre_position->next;
        position = position->next;
    }
    if (position->data != given_value)
        return LL_NODE_NOT_FOUND;
    

    //assign node to the list
    struct node *new_node = create_node(data);
    if (new_node == NULL) return LL_ERR_ALLOC;

    pre_position->next = new_node;
    new_node->next = position;

    return LL_OK;
}
LL_Status add_node_after_given_node(struct node **head, int data, int given_value)
{  
    struct node *position = *head;
    if (*head == NULL) return LL_ERR_EMPTY;

    while (position->next != NULL && position->data != given_value)
        position = position->next;
    
    if (position->data != given_value)
        return LL_NODE_NOT_FOUND;

    //assign node to the list
    struct node *after_position = position->next; 
    struct node *new_node = create_node(data);
    if (new_node == NULL) return LL_ERR_ALLOC;

    position->next = new_node;
    new_node->next = after_position;

    return LL_OK;
}
LL_Status delete_first_node(struct node **head)
{
    if (*head == NULL)
        return LL_ERR_EMPTY;

    struct node *temp_head_ptr = *head;
    *head = (*head)->next;

    free(temp_head_ptr);
    return LL_OK;
}
LL_Status delete_last_node(struct node **head)
{
    if ((*head) == NULL)
        return LL_ERR_EMPTY;
    if ((*head)->next == NULL) //if only one node exists, delete that node
    {
        free(*head);
        *head = NULL;
        return LL_OK;
    }
    struct node *pre_position =  *head;
    struct node *position = (*head)->next;
    

    while (position->next != NULL)
    {
        position = position->next;
        pre_position = pre_position->next;
    }
    //delete the node
    pre_position->next = NULL;
    free(position);
    return LL_OK;
}
LL_Status delete_given_node(struct node **head, int given_value)
{
    if ((*head) == NULL)
        return LL_ERR_EMPTY;

    struct node* position, *pre_position;
    pre_position = *head;
    position = (*head)->next;
    if ((*head)->data == given_value)
    {
        return delete_first_node(head);
                    
    }

    while (position != NULL && position->data != given_value)
    {
        position = position->next;
        pre_position = pre_position->next; 
    }
    if (position == NULL)
        return LL_NODE_NOT_FOUND;
    //delete the node
    pre_position->next = position->next;
    free(position);

    return LL_OK;
}
struct node *search_node(struct node *head, int given_value)
{
    while (head != NULL && head->data != given_value)
        head = head->next;

    return head;
}
struct node *merge_sort_linked_list(struct node *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    struct node *slow_ptr = head, *fast_ptr = head;       /*fast and slow ptr's finds middle node by incrementing in 2 to 1 ratio*/
    while (fast_ptr != NULL && fast_ptr->next != NULL)
    {
        fast_ptr = fast_ptr->next->next;
        if (fast_ptr != NULL)
            slow_ptr = slow_ptr->next;
    }
    //splits list and assigns its head nodes
    struct node *right_head_node = slow_ptr->next;
    slow_ptr->next = NULL;
    struct node *left_head_node = head; 

    struct node *left_sorted_list = merge_sort_linked_list(left_head_node);
    struct node *right_sorted_list = merge_sort_linked_list(right_head_node);
    return merge_linked_list(left_sorted_list, right_sorted_list);
}
struct node *merge_linked_list(struct node *head_node_left, struct node *head_node_right)
{
    struct node temp_node; // temp_node just used for connection we return its next member
    struct node *tail = &temp_node;
    tail->next = NULL;

    while (head_node_left != NULL && head_node_right != NULL)
    {
        if (head_node_left->data < head_node_right->data)
        {
            tail->next = head_node_left;
            head_node_left = head_node_left->next;
            
        } else {
            tail->next = head_node_right;
            head_node_right = head_node_right->next;
        }

        tail = tail->next;
    }
    //sort rest of the list
    while (head_node_left != NULL)
    {
        tail->next = head_node_left;
        head_node_left = head_node_left->next;
        tail = tail->next;
    }
    while (head_node_right != NULL)
    {
        tail->next = head_node_right;
        head_node_right = head_node_right->next;
        tail = tail->next;
    }
    tail->next = NULL;

    return temp_node.next;
}
LL_Status delete_linked_list(struct node **head)
{
    struct node *temp_ptr = *head;
    while ((*head) != NULL)
    {
        *head = (*head)->next;
        free(temp_ptr);
        temp_ptr = *head;
    }
    return LL_OK;
}