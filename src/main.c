#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "headers/main.h"
#include "headers/mem_utils.h"
#include "headers/socket_utils.h"
#include "headers/string_utils.h"

#define PORT 8080

int yes_index = -1;

int main()
{
    int client_fd;
    struct sockaddr_in server_address, cli_address;
    socklen_t sin_len = sizeof(cli_address);
    int socket = open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    set_server(&server_address, PORT);
    bind_socket(socket, &server_address);
    listen(socket, 5);
    printf("Server started on port %i\n", PORT);
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

void route(const int client_fd)
{
    const char *yes_codes[] = {"HTTP/3 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", "HTTP/3 200 OK\r\nContent-Type: text/css; charset=UTF-8\r\n\r\n", "HTTP/3 200 OK\r\nContent-Type: text/javascript; charset=UTF-8\r\n\r\n"};
    const char *endpoint = get_endpoint(client_fd), *contents = read_file(endpoint);
    char *response = NULL;
    const int response_length = (int) (strlen(yes_codes[yes_index]) + strlen(contents) + 4);
    response = err_malloc(response_length);
    snprintf(response, response_length, "%s%s\r\n\r\n", yes_codes[yes_index], contents);
    write(client_fd, response, strlen(response) - 1);
    err_free((char *) contents);
    err_free(response);
    close_socket(client_fd);
}

const char *get_endpoint(const int fd)
{
    char buffer[] = " \0", *read_ptr = (char *)err_malloc(2);
    while(read(fd, &buffer[0], 1) != 0)
    {
        read_ptr = (char *)err_realloc(read_ptr, strlen(read_ptr) + 1);
        strcat(read_ptr, &buffer[0]);
        printf("%c", buffer[0]);
        if(strstr(read_ptr, "\r\n\r\n") != NULL)
        {
            break;
        }
    }
    printf("\n");
    //Just to prevent memory leakage we're moving this to a char array
    const char contents[strlen(read_ptr)];
    strcpy((char *)contents, read_ptr);
    err_free(read_ptr);
    printf("%s\n\n", contents);
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
        else if(strstr(contents, "text/css") != NULL)
        {
            yes_index = 1;
            if(strstr(contents, "style.css") != NULL)
            {
                return "/style.css";
            }
        }
        //It's not sending text/javascript so for the meantime this is the best option
        else if(strstr(contents, ".js") != NULL)
        {
            yes_index = 2;
            if(strstr(contents, "script.js") != NULL)
            {
                return "/script.js";
            }
        }
        else if(strstr(contents, "/favicon.ico"))
        {
            return "/favicon.ico";
        }
    }
    return "no endpoint";
}
