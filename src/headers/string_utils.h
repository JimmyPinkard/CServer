#ifndef CSERVER_STRING_UTILS_H
#define CSERVER_STRING_UTILS_H
//read the contents of an html file
char *read_file(const char *filename);
//strncmp, but checks string length automatically
int string_compare(char *str1, char* str2);
#endif
