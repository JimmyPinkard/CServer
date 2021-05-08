#include "headers/string_utils.h"
#include "headers/mem_utils.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

char *read_file(const char *filename)
{
    const char dir[] = "client";
    const int path_length = strlen(filename) + strlen(dir) + 1;
    char *contents, path[path_length];
    snprintf(path, strlen(dir) + strlen(filename) + 1, "%s%sl", dir, filename);
    path[path_length - 1] = '\0';
    opendir(path);
    int file_desc = open(path, O_RDONLY);
    if(file_desc == -1)
    {
        fatal("Couldn't open file\n");
    }
    const int content_length = (int) lseek(file_desc, 0, SEEK_END);
    lseek(file_desc, 0, SEEK_SET);
    contents = err_malloc((sizeof(char) * content_length) + 1);
    read(file_desc, contents, content_length);
    contents[content_length] = '\0';
    close(file_desc);
    return contents;
}
int string_compare(char *str1, char* str2)
{
    return strncmp(str1, str2, strlen(str2)) == 0;
}