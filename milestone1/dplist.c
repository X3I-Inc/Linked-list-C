#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dplist.h"

/*
 * The real definition of struct list / struct node
 */
struct dplist_node {
    dplist_node_t* prev, * next;
    void* element;
};

struct dplist {
    dplist_node_t* head;

    void* (*element_copy)(void* src_element);
    void (*element_free)(void** element);
    int (*element_compare)(void* x, void* y);
};

dplist_t* dpl_create(
    void* (*element_copy)(void* src_element),
    void (*element_free)(void** element),
    int (*element_compare)(void* x, void* y)
) {
    dplist_t* list = malloc(sizeof(dplist_t));
    list->head = NULL;
    list->element_copy = element_copy;
    list->element_free = element_free;
    list->element_compare = element_compare;
    return list;
}

void dpl_free(dplist_t** list, bool free_element) {
    if (list == NULL || *list == NULL) return;

    dplist_node_t* curr = (*list)->head;
    while (curr != NULL) {
        dplist_node_t* next = curr->next;
        if (free_element && (*list)->element_free) {
            (*list)->element_free(&(curr->element));
        }
        free(curr);
        curr = next;
    }
    free(*list);
    *list = NULL;
}

dplist_t* dpl_insert_at_index(dplist_t* list, void* element, int index, bool insert_copy) {
    if (list == NULL) return NULL;

    dplist_node_t* new_node = malloc(sizeof(dplist_node_t));
    new_node->element = insert_copy && list->element_copy ? list->element_copy(element) : element;

    if (list->head == NULL) {
        // Case 1: Insert into an empty list
        new_node->prev = NULL;
        new_node->next = NULL;
        list->head = new_node;
    }
    else if (index <= 0) {
        // Case 2: Insert at the head
        new_node->prev = NULL;
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    else {
        // Case 3 and 4: Insert at or beyond the specified index
        dplist_node_t* ref_at_index = dpl_get_reference_at_index(list, index);
        if (ref_at_index->next == NULL && index >= dpl_size(list)) {
            // Insert at the end
            ref_at_index->next = new_node;
            new_node->prev = ref_at_index;
            new_node->next = NULL;
        }
        else {
            // Insert at a middle position
            new_node->prev = ref_at_index->prev;
            new_node->next = ref_at_index;
            if (ref_at_index->prev) ref_at_index->prev->next = new_node;
            ref_at_index->prev = new_node;
        }
    }

    return list;
}

dplist_t* dpl_remove_at_index(dplist_t* list, int index, bool free_element) {
    if (list == NULL || list->head == NULL) return NULL;

    dplist_node_t* curr = dpl_get_reference_at_index(list, index);
    if (curr == NULL) return list;

    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    }
    else {
        list->head = curr->next;
    }
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }
    if (free_element && list->element_free) {
        list->element_free(&(curr->element));
    }
    free(curr);
    return list;
}

int dpl_size(dplist_t* list) {
    if (list == NULL || list->head == NULL) return 0;
    int size = 0;
    dplist_node_t* curr = list->head;
    while (curr != NULL) {
        size++;
        curr = curr->next;
    }
    return size;
}

void* dpl_get_element_at_index(dplist_t* list, int index) {
    dplist_node_t* node = dpl_get_reference_at_index(list, index);
    return node ? node->element : NULL;
}

int dpl_get_index_of_element(dplist_t* list, void* element) {
    if (list == NULL || list->head == NULL || list->element_compare == NULL) return -1;

    int index = 0;
    dplist_node_t* curr = list->head;
    while (curr != NULL) {
        if (list->element_compare(curr->element, element) == 0) return index;
        curr = curr->next;
        index++;
    }
    return -1;
}

dplist_node_t* dpl_get_reference_at_index(dplist_t* list, int index) {
    if (list == NULL || list->head == NULL) return NULL;

    dplist_node_t* curr = list->head;
    int i = 0;
    while (curr->next != NULL && i < index) {
        curr = curr->next;
        i++;
    }
    return curr;
}

void* dpl_get_element_at_reference(dplist_t* list, dplist_node_t* reference) {
    return reference ? reference->element : NULL;
}
