#include <stdio.h>
#include <assert.h>
#include "my_malloc.h"

void test_my_malloc_and_my_free() {
    // Test 1: Allocate memory and check if the pointer is not NULL
    int *ptr_1 = (int*) my_malloc(sizeof(int));
    assert(ptr_1 != NULL); // Ensure memory allocation was successful
    *ptr_1 = 42; // Assign a value to the allocated memory
    assert(*ptr_1 == 42); // Verify the value

    // Test 2: Allocate another block and ensure it is distinct
    int *ptr_2 = (int*) my_malloc(sizeof(int));
    assert(ptr_2 != NULL);
    *ptr_2 = 84;
    assert(*ptr_2 == 84);
    assert(ptr_1 != ptr_2); // Ensure the two pointers are distinct

    // Test 3: Free a block and reallocate to check reuse
    my_free(ptr_1); // Free the first block
    int *ptr_3 = (int*) my_malloc(sizeof(int));
    assert(ptr_3 != NULL);
    *ptr_3 = 21;
    assert(*ptr_3 == 21);

    // Check if the freed block was reused
    assert(ptr_1 == ptr_3);

    // Test 4: Free all blocks and ensure no crashes
    my_free(ptr_2);
    my_free(ptr_3);

    printf("All tests passed!\n");
}

int main() {
    test_my_malloc_and_my_free();
    return 0;
}