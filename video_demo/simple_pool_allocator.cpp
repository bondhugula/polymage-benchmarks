#include<stdlib.h>
#include<assert.h>
// Linked list of allocations
struct alloc_node {
    void * alloc;
    long long int size;
    bool in_use;
    struct alloc_node * next;
};

// Start and end of the linked list
struct alloc_node * alloc_begin;
struct alloc_node * alloc_end;

// Initialize
extern "C" void pool_init() {
    alloc_begin = NULL;
    alloc_end = NULL;
}

// Allocate
void * pool_allocate(long long int buffer_size) {
    if (alloc_begin == NULL) {
        alloc_begin = (struct alloc_node * ) malloc(sizeof(struct alloc_node));
        alloc_begin->alloc = malloc(buffer_size);
        alloc_begin->size = buffer_size;
        alloc_begin->in_use = true;
        alloc_begin->next = NULL;
        alloc_end = alloc_begin;
        return alloc_begin->alloc;        
    }
    struct alloc_node * curr_node = alloc_begin;
    // Find a matching allocation which is not in use.
    while (curr_node != NULL) {
        if (curr_node->in_use != true && curr_node->size == buffer_size) {
            curr_node->in_use = true;
            return curr_node->alloc;
        }
        curr_node = curr_node->next;
    }
    // If there is no free allocation matching the size.
    // Create a new one and add it to the end of the list.
    assert(curr_node == NULL);
    alloc_end->next = (struct alloc_node * ) malloc(sizeof(struct alloc_node));
    alloc_end = alloc_end->next;
    alloc_end->alloc = malloc(buffer_size);
    alloc_end->size = buffer_size;
    alloc_end->in_use = true;
    alloc_end->next = NULL;
    return alloc_end->alloc;    
}

int pool_num_allocs() {    
    assert(alloc_begin!=NULL && alloc_end!=NULL);
    int total_allocs = 0;
    struct alloc_node * curr_node = alloc_begin;
    while (curr_node != NULL) {
        total_allocs += 1;
        curr_node = curr_node->next;
    }
    return total_allocs;   
}

long long int pool_total_alloc() {
    assert(alloc_begin!=NULL && alloc_end!=NULL);
    long long int total_bytes = 0;
    struct alloc_node * curr_node = alloc_begin;
    while (curr_node != NULL) {
        total_bytes += curr_node->size;
        curr_node = curr_node->next;
    }
    return total_bytes;
}

bool pool_alloc_in_use(void * buffer) {
    assert(alloc_begin!=NULL && alloc_end!=NULL);
    struct alloc_node * curr_node = alloc_begin;
    while (curr_node != NULL) {
        if (curr_node->alloc == buffer) 
            return curr_node->in_use;
    }
}

// De-allocate
void pool_deallocate(void * buffer) {
    assert(alloc_begin!=NULL && alloc_end!=NULL);
    struct alloc_node * curr_node = alloc_begin;
    while (curr_node != NULL) {
        if (curr_node->alloc == buffer) {
            assert(curr_node->in_use == true);
            curr_node->in_use = false;
            return;
        }
        curr_node = curr_node->next;
    }
    assert(false);
}

// Destroy all the buffers allocated in the pool.
extern "C" void pool_destroy() {
    struct alloc_node * curr_node = alloc_begin;
    while (curr_node!=NULL) {
        assert(curr_node->in_use == false);
        free(curr_node->alloc);
        struct alloc_node * prev_node = curr_node;
        curr_node = prev_node->next;
        free(prev_node);
    }
}
