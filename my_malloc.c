#include "my_malloc.h"

struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta* last, size_t size);
struct block_meta *get_block_ptr(void *ptr);

// Function to allocate memory
void *my_malloc(size_t size) {
    struct block_meta *block;

    // If this is the first allocation, initialize the global base
    if (!global_base) {
        block = request_space(NULL, size); // Request space from the system
        if (!block) return NULL;          // Return NULL if allocation fails
        global_base = block;              // Set the global base to the first block
    } else {
        struct block_meta *last = global_base;

        // Try to find a free block that fits the requested size
        block = find_free_block(&last, size);
        if (!block) {
            // If no suitable free block is found, request more space from the system
            block = request_space(last, size);
            if (!block) return NULL; // Return NULL if allocation fails
        } else {
            // If a suitable free block is found, mark it as allocated
            block->free = 0;
        }
    }

    // Return a pointer to the memory region after the metadata
    return (block + 1);
}

// Function to free allocated memory
void my_free(void* ptr) {
    if (!ptr) return; // If the pointer is NULL, do nothing

    // Retrieve the metadata block associated with the pointer
    struct block_meta* block_ptr = get_block_ptr(ptr);

    // Mark the block as free
    block_ptr->free = 1;
}

// Function to find a free block of memory that fits the requested size
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
    struct block_meta *current = global_base;

    // Traverse the linked list of memory blocks
    while (current && !(current->free && current->size >= size)) {
        *last = current;       // Keep track of the last visited block
        current = current->next; // Move to the next block
    }

    // Return the first suitable free block, or NULL if none is found
    return current;
}
    
struct block_meta *request_space(struct block_meta* last, size_t size) {
    // Use sbrk to allocate memory from the system
    struct block_meta *block = sbrk(0); // Get the current program break
    void *request = sbrk(size + META_SIZE); // Move the program break to allocate memory

    // Check if the system call failed
    if (request == (void*)-1) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Initialize the metadata for the new block
    block->size = size;       // Set the size of the block
    block->next = NULL;       // The new block does not point to any other block
    block->free = 0;          // Mark the block as allocated

    // If there is a previous block, link it to the new block
    if (last) {
        last->next = block;
    }

    return block; // Return the pointer to the newly allocated block
}

// Function to retrieve the data block associated with a given memory pointer.
// This function calculates the address of the metadata block by subtracting the
// size of the metadata structure from the given memory pointer.
//
// @param ptr A pointer to the memory region allocated by my_malloc.
// @return A pointer to the data block associated with the given memory pointer.
struct block_meta *get_block_ptr(void *ptr) {
    return (struct block_meta*)ptr - 1;
}