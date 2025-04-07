#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos para LISTA LIGADA CIRCULAR
// ----------------------------
#define DECLARE_GENERIC_CIRCULAR_LINKED_LIST(TYPE) \
    typedef struct CircularNode_##TYPE { \
        TYPE data; \
        struct CircularNode_##TYPE* next; \
    } CircularNode_##TYPE; \
    CircularNode_##TYPE* circular_node_##TYPE##__create(TYPE data);\
    void circular_node_##TYPE##__destroy(CircularNode_##TYPE* node);\
    \
    typedef struct { \
        CircularNode_##TYPE* head; \
        size_t length; \
    } CircularList_##TYPE; \
    \
    CircularList_##TYPE* circular_list_##TYPE##_create(void); \
    void circular_list_##TYPE##_destroy(CircularList_##TYPE* list); \
    bool circular_list_##TYPE##_insert(CircularList_##TYPE* list, TYPE data, size_t pos); \
    bool circular_list_##TYPE##_append(CircularList_##TYPE* list, TYPE data); \
    bool circular_list_##TYPE##_remove_at(CircularList_##TYPE* list, size_t pos); \
    bool circular_list_##TYPE##_get(const CircularList_##TYPE* list, size_t pos, TYPE* out); \
    size_t circular_list_##TYPE##_length(const CircularList_##TYPE* list); \
    void circular_list_##TYPE##_print(const CircularList_##TYPE* list, void (*print_fn)(TYPE)); \
    bool circular_list_##TYPE##_contains(const CircularList_##TYPE* list, TYPE data); \
    bool circular_list_##TYPE##_remove(CircularList_##TYPE* list, TYPE data); \
    void circular_list_##TYPE##_clear(CircularList_##TYPE* list);

// ----------------------------
// Macro para la implementación de LISTA LIGADA CIRCULAR
// ----------------------------
#define IMPLEMENT_GENERIC_CIRCULAR_LINKED_LIST(TYPE) \
    CircularNode_##TYPE* circular_node_##TYPE##__create(TYPE data){\
        CircularNode_##TYPE* new_node = malloc(sizeof(CircularNode_##TYPE)); \
        if (!new_node) return NULL; \
        new_node->data = data;\
        new_node->next = NULL;\
        return new_node;\
    }\
    \
    void circular_node_##TYPE##__destroy(CircularNode_##TYPE *node){\
        free(node);\
    }\
    \
    CircularList_##TYPE* circular_list_##TYPE##_create(void) { \
        CircularList_##TYPE* list = malloc(sizeof(CircularList_##TYPE)); \
        if (!list) return NULL; \
        list->head = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void circular_list_##TYPE##_destroy(CircularList_##TYPE* list) { \
        if (!list || !list->head) return; \
        CircularNode_##TYPE* current = list->head->next; \
        CircularNode_##TYPE* temp; \
        while (current != list->head) { \
            temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(list->head); \
        free(list); \
    } \
    \
    bool circular_list_##TYPE##_insert(CircularList_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        \
        CircularNode_##TYPE* new_node = circular_node_##TYPE##__create(data); \
        if (!new_node) return false; \
        \
        if (list->length == 0) { \
            list->head = new_node; \
            new_node->next = new_node; \
        } else if (pos == 0) { \
            new_node->next = list->head; \
            CircularNode_##TYPE* tail = list->head; \
            while (tail->next != list->head) { \
                tail = tail->next; \
            } \
            tail->next = new_node; \
            list->head = new_node; \
        } else { \
            CircularNode_##TYPE* current = list->head; \
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
    bool circular_list_##TYPE##_append(CircularList_##TYPE* list, TYPE data) { \
        return circular_list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    bool circular_list_##TYPE##_remove_at(CircularList_##TYPE* list, size_t pos) { \
        if (!list || !list->head || pos >= list->length) return false; \
        \
        CircularNode_##TYPE* to_delete = NULL; \
        \
        if (list->length == 1) { \
            to_delete = list->head; \
            list->head = NULL; \
        } else if (pos == 0) { \
            to_delete = list->head; \
            CircularNode_##TYPE* tail = list->head; \
            while (tail->next != list->head) { \
                tail = tail->next; \
            } \
            list->head = list->head->next; \
            tail->next = list->head; \
        } else { \
            CircularNode_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            to_delete = current->next; \
            current->next = to_delete->next; \
        } \
        circular_node_##TYPE##__destroy(to_delete); \
        list->length--; \
        return true; \
    } \
    \
    bool circular_list_##TYPE##_get(const CircularList_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !list->head || !out || pos >= list->length) return false; \
        \
        CircularNode_##TYPE* current = list->head; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        *out = current->data; \