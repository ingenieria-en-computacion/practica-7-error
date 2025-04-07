#define LINKED_LIST_IMPLEMENTATION
#define CIRCULAR_LINKED_LIST_IMPLEMENTATION
#include "linked_list.h"
#define CIRCULAR_LINKED_LIST_IMPLEMENTATION
#include "circular_linked_list.h"
#include <stdio.h>

void print_int(int value) {
    printf("%d", value);
}

void print_char(char value) {
    printf("%c", value);
}

void print_float(float value) {
    printf("%f", value);
}

int main() {
   
    LinkedList_int* nums = linked_list_int_create();
    linked_list_int_append(nums, 10);
    linked_list_int_append(nums, 20);
    linked_list_int_insert(nums, 15, 1);

    printf("Lista Lineal de Enteros: ");
    linked_list_int_print(nums, print_int);
    printf("Longitud: %zu\n", linked_list_int_length(nums));

    int get_val;
    if (linked_list_int_get(nums, 1, &get_val)) {
        printf("Elemento en la posición 1: %d\n", get_val);
    }

    linked_list_int_destroy(nums);
    printf("\n");

    LinkedList_char* chars = linked_list_char_create();
    linked_list_char_append(chars, 'a');
    linked_list_char_append(chars, 'c');
    linked_list_char_insert(chars, 'b', 1);

    printf("Lista Lineal de Caracteres: ");
    linked_list_char_print(chars, print_char);
    printf("Longitud: %zu\n", linked_list_char_length(chars));

    linked_list_char_destroy(chars);
    printf("\n");

 
    CircularList_float* floats = circular_list_float_create();
    circular_list_float_append(floats, 1.1f);
    circular_list_float_append(floats, 3.3f);
    circular_list_float_insert(floats, 2.2f, 1);

    printf("Lista Circular de Floats: ");
    circular_list_float_print(floats, print_float);
    printf("Longitud: %zu\n", circular_list_float_length(floats));

    float get_float_val;
    if (circular_list_float_get(floats, 0, &get_float_val)) {
        printf("Elemento en la posición 0 (circular): %f\n", get_float_val);
    }

    circular_list_float_destroy(floats);
    printf("\n");

    return 0;
}