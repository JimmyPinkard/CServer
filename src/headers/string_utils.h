#ifndef CSERVER_STRING_UTILS_H
#define CSERVER_STRING_UTILS_H
//read the contents of an html file
const char *read_file(const char *filename);
//strncmp, but checks string length automatically
int string_compare(const char * const str1, const char* const str2);
#endif
