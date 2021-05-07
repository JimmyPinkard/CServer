#ifndef CSERVER_STRING_UTILS_H
#define CSERVER_STRING_UTILS_H
//read the contents of an html file
char *read_file(char *filename);
//reads file until new line is encountered
char *cruise(int* file_desc);
//strncmp, but checks string length automatically
int string_compare(char *str1, char* str2);
//get the string from start to end-1 returns a pointer, remember to assingn it to something so you can free
char *substring(const char *str, int start, int end);
#endif
