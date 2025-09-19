#pragma once
#include <unistd.h>
#include <sys/types.h>

/**
 * Metadata structure for a memory block.
 * Contains information about the size of the block, 
 * a pointer to the next block, and whether the block is free.
 */
struct block_meta {
  size_t size;               // Size of the memory block
  struct block_meta *next;   // Pointer to the next block in the linked list
  int free;                  // Indicates if the block is free (1) or allocated (0)
};

#define META_SIZE sizeof(struct block_meta)

static void *global_base = NULL;

/**
 * Allocates a block of memory of the specified size.
 * 
 * @param size The size of the memory block to allocate (in bytes).
 * @return A pointer to the allocated memory block, or NULL if allocation fails.
 */
void *my_malloc(size_t size);

/**
 * Frees a previously allocated memory block.
 * 
 * @param ptr A pointer to the memory block to free. If NULL, no action is taken.
 */
void my_free(void* ptr);
