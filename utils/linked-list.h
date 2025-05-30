#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

// Node structure for the linked list
typedef struct ListNode {
    void* data;
    struct ListNode* next;
} ListNode;

// Function declarations
ListNode* list_create(void);
void list_add_front(ListNode** head, void* data);
void list_add_end(ListNode** head, void* data);
void* list_remove_front(ListNode** head);
void* list_remove_end(ListNode** head);
void list_print(const ListNode* head, void (*print_data)(const void*));
void list_free(ListNode* head, void (*free_data)(void*));

#endif // LINKED_LIST_H 