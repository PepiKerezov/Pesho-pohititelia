#include <stdlib.h>
#include "linked-list.h"

ListNode* list_create(void) {
    return NULL;  // Return NULL for empty list
}

void list_add_front(ListNode** head, void* data) {
    if (head == NULL) return;

    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = *head;  // Point to current head
    *head = new_node;        // Make new node the head
}

void list_add_end(ListNode** head, void* data) {
    if (head == NULL) return;

    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        ListNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void* list_remove_front(ListNode** head) {
    if (head == NULL || *head == NULL) return NULL;

    ListNode* node_to_remove = *head;
    void* data = node_to_remove->data;
    *head = node_to_remove->next;
    free(node_to_remove);

    return data;
}

void* list_remove_end(ListNode** head) {
    if (head == NULL || *head == NULL) return NULL;

    ListNode* current = *head;
    ListNode* prev = NULL;
    void* data;

    // If list has only one node
    if (current->next == NULL) {
        data = current->data;
        free(current);
        *head = NULL;
        return data;
    }

    // Find the last node
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    data = current->data;
    prev->next = NULL;
    free(current);

    return data;
}

void list_print(const ListNode* head, void (*print_data)(const void*)) {
    if (print_data == NULL) return;

    const ListNode* current = head;
    while (current != NULL) {
        print_data(current->data);
        current = current->next;
    }
}

void list_free(ListNode* head, void (*free_data)(void*)) {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* next = current->next;
        if (free_data != NULL && current->data != NULL) {
            free_data(current->data);
        }
        free(current);
        current = next;
    }
} 