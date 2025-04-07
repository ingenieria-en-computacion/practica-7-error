#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos para LISTA LIGADA
// ----------------------------
#define DECLARE_GENERIC_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    Node_##TYPE* node_##TYPE##__create(TYPE data);\
    void node_##TYPE##__destroy(Node_##TYPE* node);\
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } LinkedList_##TYPE; \
    \
    LinkedList_##TYPE* linked_list_##TYPE##_create(void); \
    void linked_list_##TYPE##_destroy(LinkedList_##TYPE* list); \
    bool linked_list_##TYPE##_insert(LinkedList_##TYPE* list, TYPE data, size_t pos); \
    bool linked_list_##TYPE##_append(LinkedList_##TYPE* list, TYPE data); \
    bool linked_list_##TYPE##_remove_at(LinkedList_##TYPE* list, size_t pos); \
    bool linked_list_##TYPE##_get(const LinkedList_##TYPE* list, size_t pos, TYPE* out); \
    size_t linked_list_##TYPE##_length(const LinkedList_##TYPE* list); \
    void linked_list_##TYPE##_print(const LinkedList_##TYPE* list, void (*print_fn)(TYPE)); \
    bool linked_list_##TYPE##_contains(const LinkedList_##TYPE* list, TYPE data); \
    bool linked_list_##TYPE##_remove(LinkedList_##TYPE* list, TYPE data); \
    void linked_list_##TYPE##_clear(LinkedList_##TYPE* list);

// ----------------------------
// Macro para la implementación de LISTA LIGADA
// ----------------------------
#define IMPLEMENT_GENERIC_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##__create(TYPE data){\
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return NULL; \
        new_node->data = data;\
        new_node->next = NULL;\
        return new_node;\
    }\
    \
    void node_##TYPE##__destroy(Node_##TYPE *node){\
        free(node);\
    }\
    \
    LinkedList_##TYPE* linked_list_##TYPE##_create(void) { \
        LinkedList_##TYPE* list = malloc(sizeof(LinkedList_##TYPE)); \
        if (!list) return NULL; \
        list->head = NULL; \
        list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void linked_list_##TYPE##_destroy(LinkedList_##TYPE* list) { \
        if (!list) return; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(list); \
    } \
    \
    bool linked_list_##TYPE##_insert(LinkedList_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        \
        Node_##TYPE* new_node = node_##TYPE##__create(data); \
        if (!new_node) return false; \
        \
        if (pos == 0) { \
            new_node->next = list->head; \
            list->head = new_node; \
            if (!list->tail) list->tail = new_node; \
        } else if (pos == list->length) { \
            if (list->tail) { \
                list->tail->next = new_node; \
            } else { \
                list->head = new_node; \
            } \
            list->tail = new_node; \
            new_node->next = NULL; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            new_node->next = current->next; \
            current->next = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    \
    bool linked_list_##TYPE##_append(LinkedList_##TYPE* list, TYPE data) { \
        return linked_list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    bool linked_list_##TYPE##_remove_at(LinkedList_##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        \
        Node_##TYPE* to_delete = NULL; \
        \
        if (pos == 0) { \
            to_delete = list->head; \
            list->head = list->head->next; \
            if (!list->head) list->tail = NULL; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            to_delete = current->next; \
            current->next = to_delete->next; \
            if (pos == list->length - 1) { \
                list->tail = current; \
            } \
        } \
        node_##TYPE##__destroy(to_delete); \
        list->length--; \
        return true; \
    } \
    \
    bool linked_list_##TYPE##_get(const LinkedList_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        *out = current->data; \
        return true; \
    } \
    \
    size_t linked_list_##TYPE##_length(const LinkedList_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    \
    bool linked_list_##TYPE##_contains(const LinkedList_##TYPE* list, TYPE data) { \
        if (!list) return false; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            if (current->data == data) { \
                return true; \
            } \
            current = current->next; \
        } \
        return false; \
    } \
    \
    bool linked_list_##TYPE##_remove(LinkedList_##TYPE* list, TYPE data) { \
        if (!list) return false; \
        Node_##TYPE* prev = NULL; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            if (current->data == data) { \
                if (prev) { \
                    prev->next = current->next; \
                    if (!current->next) { \
                        list->tail = prev; \
                    } \
                } else { \
                    list->head = current->next; \
                    if (!list->head) { \
                        list->tail = NULL; \
                    } \
                } \
                node_##TYPE##__destroy(current); \
                list->length--; \
                return true; \
            } \
            prev = current; \
            current = current->next; \
        } \
        return false; \
    } \
    \
    void linked_list_##TYPE##_clear(LinkedList_##TYPE* list) { \
        if (!list) return; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        list->head = NULL; \
        list->tail = NULL; \
        list->length = 0; \
    } \
    \
    void linked_list_##TYPE##_print(const LinkedList_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn) return; \
        printf("["); \
        Node_##TYPE* current = list->head; \
        while (current) { \
            print_fn(current->data); \
            if (current->next) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    }

// Declaraciones para tipos concretos
DECLARE_GENERIC_LINKED_LIST(int)
DECLARE_GENERIC_LINKED_LIST(char)
DECLARE_GENERIC_LINKED_LIST(float)

#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_GENERIC_LINKED_LIST(int)
IMPLEMENT_GENERIC_LINKED_LIST(char)
IMPLEMENT_GENERIC_LINKED_LIST(float)
#endif