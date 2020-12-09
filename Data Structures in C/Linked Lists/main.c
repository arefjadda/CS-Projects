#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linkedlist.h"

typedef struct Node{
    int val;
    struct Node* next;
} node;

void print_list(node* head){
    node* temp = head;

    while(temp != NULL){
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("|\n");
}

node* new_node(int val){
    node* out = malloc(sizeof(node));
    out->val = val;
    out->next = NULL;
    return out;
}

node* prepend(node** head, node** tail, int val){
    node* temp = new_node(val);
    temp->next = *head;
    if (*head == NULL){
        *tail = temp;
    }
    *head = temp;
    return temp;
}

node* append(node** head, node** tail, int val){
    node* temp = new_node(val);
    if (*head == NULL){
        *head = temp;
        *tail = temp;
    } else{
        node* temp2 = *tail;
        temp2->next = temp;
        temp2 = temp;
        *tail = temp2;
    }
    return temp;
}

node* find_node(node* head, int val){
    node* temp = head;
    while(temp != NULL){
        if (temp->val == val) return temp;
        temp = temp->next;
    }
    printf("This value doesn't exist in the list.\n");
    return NULL;
}

bool node_exists(node* head, int val){
    node* temp = head;
    while(temp != NULL){
        if (temp->val == val) return true;
        temp = temp->next;
    }
    return false;
}

void insert_node(int val, int index, node* head){
    int ind = 0;
    node* temp = head;
    node* temp2 = new_node(val);
    while((ind < (index - 1)) && (temp != NULL)){
        temp = temp->next;
        ind++;
    }
    if (temp != NULL){
        temp2->next = temp->next;
        temp->next = temp2;
    } else printf("The index you input is invalid (it might exceed the size of the list).\n");
}

void remove_index(int index, node* head){
    int ind = 0;
    node* temp = head;
    node* temp2;
    while(temp != NULL){
        if (ind == index){
            temp2->next = temp->next;
            free(temp);
            return;
        }
        temp2 = temp;
        temp = temp->next;
        ind++;
    }
    printf("This index value is invalid.\n");
}

void remove_val(int val, node* head){
    node* temp = head;
    node* temp2;
    while(temp != NULL){
        if (temp->val == val){
            temp2->next = temp->next;
            free(temp);
            return;
        }
        temp2 = temp;
        temp = temp->next;
    }
    printf("This input value was not found in the list.\n");
}

int main()
{
    node* head = NULL;
    node* tail = NULL;

    for (int i; i < 5; i++){
        append(&head, &tail, i);
    }

    insert_node(31, 1, head);

    remove_index(32, head);

    remove_val(39, head);

    printf("%d\n", node_exists(head, 31));

    print_list(head);

    return 0;
}
