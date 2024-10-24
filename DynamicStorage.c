#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a memory block
struct Block {
    int size;
    int is_free;
    int block_id;
    struct Block* next;
};

// Function to create a new block
struct Block* createBlock(int block_id, int size) {
    struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
    newBlock->block_id = block_id;
    newBlock->size = size;
    newBlock->is_free = 1; // initially the block is free
    newBlock->next = NULL;
    return newBlock;
}

// Function to initialize memory blocks
void initializeMemory(struct Block** head, int blocks[], int n) {
    struct Block* temp = NULL;
    for (int i = 0; i < n; i++) {
        struct Block* newBlock = createBlock(i + 1, blocks[i]);
        if (*head == NULL) {
            *head = newBlock;
            temp = *head;
        } else {
            temp->next = newBlock;
            temp = temp->next;
        }
    }
}

// Function to implement First Fit allocation
void firstFit(struct Block* head, int process_size) {
    struct Block* temp = head;
    while (temp != NULL) {
        if (temp->is_free && temp->size >= process_size) {
            temp->is_free = 0;
            printf("Process of size %d allocated to block %d (size: %d)\n", process_size, temp->block_id, temp->size);
            return;
        }
        temp = temp->next;
    }
    printf("No suitable block found for process of size %d in First Fit.\n", process_size);
}

// Function to implement Best Fit allocation
void bestFit(struct Block* head, int process_size) {
    struct Block* temp = head;
    struct Block* best_fit = NULL;
    
    while (temp != NULL) {
        if (temp->is_free && temp->size >= process_size) {
            if (best_fit == NULL || temp->size < best_fit->size) {
                best_fit = temp;
            }
        }
        temp = temp->next;
    }

    if (best_fit != NULL) {
        best_fit->is_free = 0;
        printf("Process of size %d allocated to block %d (size: %d)\n", process_size, best_fit->block_id, best_fit->size);
    } else {
        printf("No suitable block found for process of size %d in Best Fit.\n", process_size);
    }
}

// Function to free a block
void freeBlock(struct Block* head, int block_id) {
    struct Block* temp = head;
    while (temp != NULL) {
        if (temp->block_id == block_id) {
            temp->is_free = 1;
            printf("Block %d (size: %d) freed.\n", block_id, temp->size);
            return;
        }
        temp = temp->next;
    }
    printf("No block found with ID %d.\n", block_id);
}

// Function to print memory blocks
void printMemory(struct Block* head) {
    struct Block* temp = head;
    printf("Memory blocks:\n");
    while (temp != NULL) {
        printf("Block %d: size = %d, %s\n", temp->block_id, temp->size, temp->is_free ? "free" : "allocated");
        temp = temp->next;
    }
}

int main() {
    struct Block* memory = NULL;
    int blocks[] = {100, 500, 200, 300, 600}; // Memory blocks
    int n = sizeof(blocks) / sizeof(blocks[0]);

    // Initialize memory
    initializeMemory(&memory, blocks, n);
    printMemory(memory);

    // First Fit allocation
    printf("\nFirst Fit Allocation:\n");
    firstFit(memory, 120);
    firstFit(memory, 400);
    firstFit(memory, 350);

    printMemory(memory);

    // Freeing some blocks
    printf("\nFreeing block 1 and 2:\n");
    freeBlock(memory, 1);
    freeBlock(memory, 2);
    printMemory(memory);

    // Best Fit allocation
    printf("\nBest Fit Allocation:\n");
    bestFit(memory, 200);
    bestFit(memory, 450);

    printMemory(memory);

    return 0;
}