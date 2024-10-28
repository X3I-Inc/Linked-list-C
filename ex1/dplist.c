/**
 * \author Jeroen Van Aken, Bert Lagaisse, Ludo Bruynseels
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "dplist.h"



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
    dplist_t *Linkedlist;
    Linkedlist = malloc(sizeof(struct dplist));
    Linkedlist->head = NULL;
  return Linkedlist;
}

void dpl_free(dplist_t **list) {

    if (list == NULL || *list == NULL) return;

    dplist_node_t *curr = (*list)->head;
    dplist_node_t *next; //next node

    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
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
    list_node->element = element;
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
    dplist_node_t *curr = list->head;
    if(index <= dpl_size(list))
    {
        curr = dpl_get_reference_at_index(list, index);
    }

    if(curr == NULL) return NULL;

    if (curr->prev != NULL) { // Not the head node
        curr->prev->next = curr->next;
    } else { // Head node
        list->head = curr->next;
    }

    if (curr->next != NULL) { // Not the tail node
        curr->next->prev = curr->prev;
    }

    // Free the node
    free(curr);

    //TODO: add your code here
    return NULL;
}

int dpl_size(dplist_t *list) {
    if(list == NULL || list->head == NULL) return 0;
    dplist_node_t *curr = list->head;
    int i = 0;
    while(curr != NULL)
    {
        curr = curr->next;
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



