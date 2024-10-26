/**
 * \author Jeroen Van Aken, Bert Lagaisse, Ludo Bruynseels
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "dplist.h"
#include <string.h>



/*
 * The real definition of struct list / struct node
 */
struct dplist_node {
    dplist_node_t *prev, *next;
    element_t element;
};

struct dplist {
    dplist_node_t *head;
    // more fields will be added later
};

dplist_t *dpl_create() {
    dplist_t *list;
    list = malloc(sizeof(struct dplist));
    list->head = NULL;
  return list;
}

//allocates memory and saves copy of th string returning the pointer to the allocated memory
#ifndef strdup
char *strdup(const char *s){
size_t len = strlen(s) + 1;
char *copy = malloc(len);
if(copy){
  memcpy(copy, s, len);
  }
  return copy;
}
#endif

void dpl_free(dplist_t **list) {

    if (list == NULL || *list == NULL) return;

    dplist_node_t *current = (*list)->head;
    dplist_node_t *next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current->element);
        free(current);
        current = next_node;
    }

    free(*list);

    *list = NULL;
    //TODO: add your code here
    //Do extensive testing with valgrind.

}

/* Important note: to implement any list manipulation operator (insert, append, delete, sort, ...), always be aware of the following cases:
 * 1. empty list ==> avoid errors
 * 2. do operation at the start of the list ==> typically requires some special pointer manipulation
 * 3. do operation at the end of the list ==> typically requires some special pointer manipulation
 * 4. do operation in the middle of the list ==> default case with default pointer manipulation
 * ALWAYS check that you implementation works correctly in all these cases (check this on paper with list representation drawings!)
 **/


dplist_t *dpl_insert_at_index(dplist_t *list, element_t element, int index) {
    dplist_node_t *ref_at_index, *list_node;
    if (list == NULL) return NULL;

    list_node = malloc(sizeof(dplist_node_t));

    list_node->element = strdup(element);
    /*
you can ofc assign original pointer of element without duplicating, however there can be few consequensec.
Consequences:
Pointer Issues: By not duplicating the string, all nodes will point
to the same memory location if the same string is used. If the original
string is modified or freed, it affects all pointers to that string.

Memory Management: Since you are not allocating new memory for each element,
freeing the list becomes problematic. Attempting to free the same memory
multiple times will lead to undefined behavior and program crashes.
     */

    // pointer drawing breakpoint
    if (list->head == NULL) { // covers case 1
        list_node->prev = NULL;
        list_node->next = NULL;
        list->head = list_node;
        // pointer drawing breakpoint
    } else if (index <= 0) { // covers case 2
        list_node->prev = NULL;
        list_node->next = list->head;
        list->head->prev = list_node;
        list->head = list_node;
        // pointer drawing breakpoint
    } else {
        ref_at_index = dpl_get_reference_at_index(list, index);
        assert(ref_at_index != NULL);
        // pointer drawing breakpoint
        if (index < dpl_size(list)) { // covers case 4
            list_node->prev = ref_at_index->prev;
            list_node->next = ref_at_index;
            ref_at_index->prev->next = list_node;
            ref_at_index->prev = list_node;
            // pointer drawing breakpoint
        } else { // covers case 3
            assert(ref_at_index->next == NULL);
            list_node->next = NULL;
            list_node->prev = ref_at_index;
            ref_at_index->next = list_node;
            // pointer drawing breakpoint
        }
    }

    return list;
}

dplist_t *dpl_remove_at_index(dplist_t *list, int index) {

    if (list == NULL || list->head == NULL) return NULL;

    dplist_node_t *current = list->head;

    if(index <= dpl_size(list))
    {
        current = dpl_get_reference_at_index(list, index);
    }

    if(current == NULL) return NULL;

    if (current->prev != NULL) { // Not the head node
        current->prev->next = current->next;
    } else { // Head node
        list->head = current->next;
    }

    if (current->next != NULL) { // Not the tail node
        current->next->prev = current->prev;
    }

    // Free the node
    free(current);

    //TODO: add your code here
    return NULL;
}

int dpl_size(dplist_t *list) {
    if(list == NULL || list->head == NULL) return 0;
    dplist_node_t *current = list->head;
    int i = 0;
    while(current != NULL && current->next)
    {
        current = current->next;
        i++;
    }
    //free(current);
    //TODO: add your code here
    return i;
}

dplist_node_t *dpl_get_reference_at_index(dplist_t *list, int index) {
    //int count = 0 ;
    if (list == NULL || list->head == NULL) return 0;
    dplist_node_t *dummy = list->head;
    int i = 0;

    while(dummy != NULL && i<index && dummy->next != NULL)
    {
        dummy = dummy -> next;
        i++;
    }


    //TODO: add your code here
    return dummy;
}

element_t dpl_get_element_at_index(dplist_t *list, int index) {

    if (list == NULL || list->head == NULL) return 0;

    dplist_node_t *dummy = dpl_get_reference_at_index(list, index);

    /* also possible as follows
    dplist_node_t *dummy = list->head;
    int i = 0;

    while(dummy != NULL && i<index && dummy->next != NULL)
    {
        dummy = dummy -> next;
        i++;
    }*/


    //TODO: add your code here
    return dummy->element;

}

int dpl_get_index_of_element(dplist_t *list, element_t element) {

    if (list == NULL || list->head == NULL) return 0;
    dplist_node_t *dummy = list->head;
    int i = 0;

    while(dummy != NULL && dummy->next != NULL)
    {
        if(dpl_get_element_at_index(list, i) == element)
        {
            break;
        }
        dummy = dummy -> next;
        i++;
    }
    //TODO: add your code here
    return i;
}



