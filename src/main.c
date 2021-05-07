#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "headers/main.h"
#include "headers/mem_utils.h"
#include "headers/socket_utils.h"
#include "headers/string_utils.h"

const int port = 8080;
const char *yes_codes[] = {"HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", "HTTP/1.1 200 OK\r\nContent-Type: text/css; charset=UTF-8\r\n\r\n", "HTTP/1.1 200 OK\r\nContent-Type: text/javascript; charset=UTF-8\r\n\r\n"};
int yes_index = -1;
char *get_endpoint(int fd)
{
    char buffer[] = " \0", *read_ptr = (char *)err_malloc(2);
    while(read(fd, &buffer[0], 1) != 0)
    {
        read_ptr = (char *)err_realloc(read_ptr, strlen(read_ptr) + 1);
        strcat(read_ptr, &buffer[0]);
        if(strstr(read_ptr, "\r\n\r\n") != NULL)
        {
            break;
        }
    }
    char contents[strlen(read_ptr)];
    strcpy(contents, read_ptr);
    err_free(read_ptr);
    //printf("%s\n", contents);
    if(strstr(contents, "GET") != NULL)
    {
        if(strstr(contents, "text/html") != NULL)
        {
            yes_index = 0;
            if(strstr(contents, "/ez") != NULL)
            {
                return "/ez.html";
            }
            else if(strstr(contents, "/") != NULL)
            {
                return "/index.html";
            }
            else
            {
                return "no endpoint";
            }
        }
        else if(strstr(contents, ".css") != NULL)
        {
            yes_index = 1;
            if(strstr(contents, "style.css") != NULL)
            {
                return "/style.css";
            }
            
        }
        else if(strstr(contents, ".js") != NULL)
        {
            yes_index = 2;
            if(strstr(contents, "script.js") != NULL)
            {
                return "/script.js";
            }
        }
    }
    return "no endpoint";
}

void route(int client_fd)
{
    char *endpoint = get_endpoint(client_fd), *contents, *response;
    contents = read_file(endpoint);
    int response_length = strlen(yes_codes[yes_index]) + strlen(contents) + 5;
    response = err_malloc(response_length);
    snprintf(response, response_length, "%s%s\r\n\r\n\0", yes_codes[yes_index], contents);
    //printf("%s\n", contents);
    write(client_fd, response, strlen(response) - 1);
    //printf("%s\n", response);
    err_free(contents);
    err_free(response);
    shutdown(client_fd, 2);
    close(client_fd);
}

int main()
{
    int client_fd;
    struct sockaddr_in server_address, cli_address;
    socklen_t sin_len = sizeof(cli_address);
    int socket = open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    set_server(&server_address, port);
    bind_socket(socket, &server_address);
    listen(socket, 5);
    printf("Server started on port %i\n", port);
    while(1)
    {
        client_fd = accept(socket, (struct sockaddr *) &cli_address, &sin_len);
        if(client_fd == -1)
        {
            perror("Can't accept\n");
            continue;
        }
        route(client_fd);
    }
}