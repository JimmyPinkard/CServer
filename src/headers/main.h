#ifndef CSERVER_MAIN_H
#define CSERVER_MAIN_H
typedef struct Request
{
    char *method;
    char *endpoint;
    char *url;
    char *content_type;
    char *file_contents;
    char *response;
}Request;

int main();
int open_socket(int domain, int type, int protocol);
Request *parse_request(int* file_desc);
#endif //CSERVER_MAIN_H
