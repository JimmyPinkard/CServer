#ifndef CSERVER_MEM_UTILS_H
#define CSERVER_MEM_UTILS_H
//If there is an error report it
void fatal(char *msg);
//Error check and allocate or free memory
void *err_malloc(unsigned int size);
void *err_realloc(void *ptr, unsigned int size);
void err_free(void* ptr);
#endif //CSERVER_MEM_UTILS_H
