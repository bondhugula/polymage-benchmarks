/*
  Copyright (c) 2015 Indian Institute of Science
  All rights reserved.

  Written and provided by:
  Ravi Teja Mullapudi, Vinay Vasista, Uday Bondhugula
  Dept of Computer Science and Automation
  Indian Institute of Science
  Bangalore 560012
  India

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. Neither the name of the Indian Institute of Science nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS MATERIAL IS PROVIDED BY Ravi Teja Mullapudi, Vinay Vasista, and Uday
  Bondhugula, Indian Institute of Science ''AS IS'' AND ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING,
  BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Ravi Teja Mullapudi, Vinay
  Vasista, CSA Indian Institute of Science BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
