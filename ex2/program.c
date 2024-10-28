#define _GNU_SOURCE
/**
 * \author Bert Lagaisse
 *
 * main method that executes some test functions (without check framework)
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dplist.h"

void ck_assert_msg(bool result, char *msg) {
    if (result) printf("%s\n", msg);
}

int main(void) {
    dplist_t *strings = NULL;
    strings = dpl_create();

    ck_assert_msg(strings != NULL, "strings = NULL, List not created");
    ck_assert_msg(dpl_size(strings) == 0, "List must not contain elements.");

    // Test inserting strings
    dpl_insert_at_index(strings, "hello", 0); //inserts string "hello" at index 0
    ck_assert_msg(dpl_size(strings) == 1, "List contains 1 element.");
    ck_assert_msg(strcmp(dpl_get_element_at_index(strings, 0), "hello") == 0, "First element is 'hello'.");
    printf("Element at index 0 is %s \n", (char*)dpl_get_element_at_index(strings, 0));

    dpl_insert_at_index(strings, "world", -1);  // Insert at head
    ck_assert_msg(dpl_size(strings) == 2, "List contains 2 elements.");
    ck_assert_msg(strcmp(dpl_get_element_at_index(strings, 0), "world") == 0, "First element is 'world'.");
    ck_assert_msg(strcmp(dpl_get_element_at_index(strings, 1), "hello") == 0, "Second element is 'hello'.");

    dpl_insert_at_index(strings, "by emil", 100);  // Insert at tail
    ck_assert_msg(dpl_size(strings) == 3, "List contains 3 elements.");
    ck_assert_msg(strcmp(dpl_get_element_at_index(strings, 2), "by emil") == 0, "Third element is 'by emil'.");
    printf("%s \n", dpl_get_element_at_index(strings, 2));
    // Test removing elements
    dpl_remove_at_index(strings, 1);  // Remove "hello"
    ck_assert_msg(dpl_size(strings) == 2, "List contains 2 elements.");
    ck_assert_msg(strcmp(dpl_get_element_at_index(strings, 0), "world") == 0, "First element is 'world'.");
    ck_assert_msg(strcmp(dpl_get_element_at_index(strings, 1), "by emil") == 0, "Second element is 'by emil'.");

    // Clean up
    dpl_free(&strings);
    ck_assert_msg(strings == NULL, "List must be NULL");

    return 0;
}
