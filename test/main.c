#include <check.h>
#include <stdlib.h>
#define LINKED_LIST_IMPLEMENTATION
#define CIRCULAR_LINKED_LIST_IMPLEMENTATION
#include "linked_list.h"
#include "circular_linked_list.h"

void print_int(int value) {
    printf("%d ", value);
}

bool int_cmp(int a, int b) {
    return a == b;
}

START_TEST(test_linked_list_create) {
    LinkedList_int* list = linked_list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_ptr_null(list->tail);
    ck_assert_uint_eq(list->length, 0);
    linked_list_int_destroy(list);
}
END_TEST

START_TEST(test_linked_list_append_and_length) {
    LinkedList_int* list = linked_list_int_create();
    ck_assert(linked_list_int_append(list, 10));
    ck_assert_uint_eq(linked_list_int_length(list), 1);
    ck_assert(linked_list_int_append(list, 20));
    ck_assert_uint_eq(linked_list_int_length(list), 2);
    linked_list_int_destroy(list);
    ck_assert_ptr_null(list);
}
END_TEST

START_TEST(test_linked_list_insert_and_get) {
    LinkedList_int* list = linked_list_int_create();
    int value = 0;
    linked_list_int_insert(list, 10, 0);
    linked_list_int_insert(list, 30, 1);
    linked_list_int_insert(list, 20, 1);
    ck_assert(linked_list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 20);
    linked_list_int_destroy(list);
}
END_TEST

START_TEST(test_linked_list_remove_at) {
    LinkedList_int* list = linked_list_int_create();
    linked_list_int_append(list, 10);
    linked_list_int_append(list, 20);
    linked_list_int_append(list, 30);
    ck_assert(linked_list_int_remove_at(list, 1));
    ck_assert_uint_eq(linked_list_int_length(list), 2);
    int value = 0;
    ck_assert(linked_list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 30);
    linked_list_int_destroy(list);
}
END_TEST

START_TEST(test_circular_list_create) {
    CircularList_int* list = circular_list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_uint_eq(list->length, 0);
    circular_list_int_destroy(list);
}
END_TEST

START_TEST(test_circular_list_append_and_length) {
    CircularList_int* list = circular_list_int_create();
    ck_assert(circular_list_int_append(list, 10));
    ck_assert_uint_eq(circular_list_int_length(list), 1);
    ck_assert_ptr_eq(list->head->next, list->head);
    ck_assert(circular_list_int_append(list, 20));
    ck_assert_uint_eq(circular_list_int_length(list), 2);
    ck_assert_ptr_eq(list->head->next->next, list->head);
    circular_list_int_destroy(list);
    ck_assert_ptr_null(list);
}
END_TEST

START_TEST(test_circular_list_insert_and_get) {
    CircularList_int* list = circular_list_int_create();
    int value = 0;
    circular_list_int_insert(list, 10, 0);
    circular_list_int_insert(list, 30, 1);
    circular_list_int_insert(list, 20, 1);
    ck_assert(circular_list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 20);
    ck_assert_ptr_eq(list->head->next->next->next, list->head);
    circular_list_int_destroy(list);
}
END_TEST

START_TEST(test_circular_list_remove_at) {
    CircularList_int* list = circular_list_int_create();
    circular_list_int_append(list, 10);
    circular_list_int_append(list, 20);
    circular_list_int_append(list, 30);
    ck_assert(circular_list_int_remove_at(list, 1));
    ck_assert_uint_eq(circular_list_int_length(list), 2);
    ck_assert_ptr_eq(list->head->next->next, list->head);
    int value = 0;
    ck_assert(circular_list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 30);
    circular_list_int_destroy(list);
}
END_TEST

Suite* linked_list_suite(void){
    Suite* s = suite_create("Linked List");
    TCase* tc_linked_core = tcase_create("Linked List Core Functions");
    tcase_add_test(tc_linked_core, test_linked_list_create);
    tcase_add_test(tc_linked_core, test_linked_list_append_and_length);
    tcase_add_test(tc_linked_core, test_linked_list_insert_and_get);
    tcase_add_test(tc_linked_core, test_linked_list_remove_at);
    suite_add_tcase(s, tc_linked_core);
    TCase* tc_circular_core = tcase_create("Circular Linked List Core Functions");
    tcase_add_test(tc_circular_core, test_circular_list_create);
    tcase_add_test(tc_circular_core, test_circular_list_append_and_length);
    tcase_add_test(tc_circular_core, test_circular_list_insert_and_get);
    tcase_add_test(tc_circular_core, test_circular_list_remove_at);
    suite_add_tcase(s, tc_circular_core);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr = srunner_create(linked_list_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}