#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int val;
    struct Node* next;
} node;

typedef struct {
    node* head;
    node* tail;
    int size;
} linkedl;

void init_ll(linkedl* llist){
    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;
}

void print_list(linkedl* llist){
    node* temp = llist->head;

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

node* prepend(linkedl* llist, int val){
    node* temp = new_node(val);
    temp->next = llist->head;
    if (llist->head == NULL){
        llist->tail = temp;
    }
    llist->head = temp;
    llist->size++;
    return temp;
}

node* append(linkedl* llist, int val){
    node* temp = new_node(val);
    if (llist->head == NULL){
        llist->head = temp;
        llist->tail = temp;
    } else{
        node* temp2 = llist->tail;
        temp2->next = temp;
        temp2 = temp;
        llist->tail = temp2;
    }
    llist->size++;
    return temp;
}

node* find_node(linkedl* llist, int val){
    node* temp = llist->head;
    while(temp != NULL){
        if (temp->val == val) return temp;
        temp = temp->next;
    }
    printf("This value doesn't exist in the list.\n");
    return NULL;
}

bool node_exists(linkedl* llist, int val){
    node* temp = llist->head;
    while(temp != NULL){
        if (temp->val == val) return true;
        temp = temp->next;
    }
    return false;
}

void insert_node(int val, int index, linkedl* llist){
    int ind = 0;
    node* temp = llist->head;
    node* temp2 = new_node(val);
    while((ind < (index - 1)) && (temp != NULL)){
        temp = temp->next;
        ind++;
    }
    if (temp != NULL){
        temp2->next = temp->next;
        temp->next = temp2;
        llist->size++;
    } else printf("The index you input is invalid (it might exceed the size of the list).\n");
}

void remove_index(int index, linkedl* llist){
    int ind = 0;
    node* temp = llist->head;
    node* temp2;
    while(temp != NULL){
        if (ind == index){
            temp2->next = temp->next;
            llist->size--;
            free(temp);
            return;
        }
        temp2 = temp;
        temp = temp->next;
        ind++;
    }
    printf("This index value is invalid.\n");
}

void remove_val(int val, linkedl* llist){
    node* temp = llist->head;
    node* temp2;

    if (llist->head->val == val){
        llist->head = llist->head->next;
        return;
    } else {
        while(temp != NULL){
            if (temp->val == val){
                temp2->next = temp->next;
                llist->size--;
                free(temp);
                return;
            }
            temp2 = temp;
            temp = temp->next;
        }
    }
    printf("This input value was not found in the list.\n");
}

void merge_lists(linkedl* list1, linkedl* list2){
    list1->tail->next = list2->head;
    list1->tail = list2->tail;
    list1->size = list1->size + list2->size;
}

void update_val(linkedl* llist, int index, int val){
    int ind = 0;
    node* temp = llist->head;
    while(temp != NULL){
        if (ind == index){
            temp->val = val;
            return;
        }
        temp = temp->next;
        ind++;
    }
    printf("This index value is invalid.\n");
}

linkedl* merge_sort(linkedl* llist, linkedl* list1, linkedl* list2, char dir[4]){

    linkedl sorted;
    init_ll(&sorted);
    append(&sorted, 0);
    linkedl current = sorted;

    if(strcmp(dir, "asc") == 0) {
        while(list1->head != NULL && list2->head != NULL){
            if(list1->head->val <= list2->head->val){
                current.head->next = list1->head;
                list1->head = list1->head->next;
            } else{
                current.head->next = list2->head;
                list2->head = list2->head->next;
            }
            current.head = current.head->next;
        }
    }

    if(strcmp(dir, "desc") == 0) {
        while(list1->head != NULL && list2->head != NULL){
            if(list1->head->val <= list2->head->val){
                current.head->next = list2->head;
                list2->head = list2->head->next;
            } else{
                current.head->next = list1->head;
                list1->head = list1->head->next;
            }
            current.head = current.head->next;
        }
    }

    if(list1->head != NULL){
        current.head->next = list1->head;
        list1->head = list1->head->next;
    }
    if(list2->head != NULL){
        current.head->next = list2->head;
        list2->head = list2->head->next;
    }
    llist->tail = current.head->next;
    llist->head = sorted.head->next;

    return sorted.head->next;
}

linkedl* sort_list(linkedl* llist, char dir[4]){

    if(strcmp(dir, "asc") != 0 && strcmp(dir, "desc") != 0){
        printf("Please choose a valid direction for the sort.\n\"asc\" for ascending values or \"desc\" for descending values.\n");
        return llist->head;
    }

    if(llist->head->next == NULL) return llist->head;

    linkedl left = *llist;
    linkedl right = *llist;

    node* temp = left.head;
    node* slow = right.head;
    node* fast = right.head;

    while(fast != NULL && fast->next != NULL){
        temp = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    temp->next = NULL;
    left.head = llist->head;
    right.head = slow;

    linkedl* left_branch = sort_list(&left, dir);
    linkedl* right_branch = sort_list(&right, dir);

    return merge_sort(llist, &left_branch, &right_branch, dir);
}

int main()
{
    linkedl mylist, myseclist;

    init_ll(&mylist);
    init_ll(&myseclist);

    for (int i = 3; i < 5; i++){
        append(&mylist, i);
    }
    for (int j = 0; j < 10; j++){
        append(&myseclist, j);
    }

    merge_lists(&mylist, &myseclist);

    insert_node(31, 1, &mylist);

    remove_index(32, &mylist);

    remove_val(39, &mylist);

    printf("%d\n", node_exists(&mylist, 4));

    update_val(&mylist, 2, 9);

    remove_val(0, &mylist);

    remove_val(0, &mylist);

    insert_node(34, 0, &mylist);
    insert_node(33, 10, &mylist);

//    sort_list(&mylist, "desc");

    print_list(&mylist);
    printf("This list's size: %d\n", mylist.size);

//  functions to add for linked lists: update a nodes value by value or index, merge 2 linked lists, sort, also add size to the linkel struct

    return 0;
}
