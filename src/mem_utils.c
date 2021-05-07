#include "headers/mem_utils.h"
#include <stdio.h>
#include <stdlib.h>
void fatal(char *msg)
{
    perror(msg);
    exit(-1);
}
void *err_malloc(unsigned int size)
{
    void *ptr = malloc(size);
    if(ptr == NULL)
    {
        fatal("Could not malloc memory\n");
        exit(-1);
    }
    return ptr;
}
void *err_realloc(void *ptr, unsigned int size)
{
    ptr = realloc(ptr, size);
    if(ptr == NULL)
    {
        fatal("Could not realloc memory\n");
    }
    return ptr;
}
void err_free(void* ptr)
{
    if(ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}