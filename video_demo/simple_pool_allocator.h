extern "C" void pool_init();
void *pool_allocate(long long int);
void pool_deallocate(void *);
extern "C" void pool_destroy();
int pool_num_allocs();
long long int pool_total_alloc();
bool pool_alloc_in_use(void * buffer);
