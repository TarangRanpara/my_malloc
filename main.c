#include <stdio.h>
#include "my_malloc.h"

int main() {
    int *ptr_1 = (int*) my_malloc(sizeof(int));
    *ptr_1 = 1;
    
    int *ptr_2 = (int*) my_malloc(sizeof(int));
    *ptr_2 = 2;

    int *ptr_3 = (int*) my_malloc(sizeof(int));
    *ptr_3 = 3;

    printf("ptr_1 = %p, value = %d\n", ptr_1, *ptr_1);
    printf("ptr_2 = %p, value = %d\n", ptr_2, *ptr_2);
    printf("ptr_3 = %p, value = %d\n", ptr_3, *ptr_3);

    my_free(ptr_2);
    ptr_2 = (int*) my_malloc(sizeof(int));
    *ptr_2 = 4;
    
    printf("ptr_1 = %p, value = %d\n", ptr_1, *ptr_1);
    printf("ptr_2 = %p, value = %d\n", ptr_2, *ptr_2);
    printf("ptr_3 = %p, value = %d\n", ptr_3, *ptr_3);

    return 0;
}