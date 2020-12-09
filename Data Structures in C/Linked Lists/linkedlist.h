#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct Node node;

node* new_node(int val);

void print_list(node* head);

node* prepend(node** head, node** tail, int val);

node* append(node** head, node** tail, int val);

node* find_node(node* head, int val);

bool node_exists(node* head, int val);

void insert_node(int val, int index, node* head);

void remove_index(int index, node* head);

void remove_val(int val, node* head);

#endif // __LINKEDLIST_H__
