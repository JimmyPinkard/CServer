#include <err.h>
#include <netdb.h>
#include <unistd.h>
#include "headers/socket_utils.h"
int open_socket(int domain, int type, int protocol)
{
    int sock = socket(domain, type, protocol);
    if(socket < 0)
    {
        err(1, "Can't open socket");
    }
    int one = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
    return sock;
}
void set_server(struct sockaddr_in *server_address, int port)
{
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = INADDR_ANY;
    server_address->sin_port = htons(port);
}
int bind_socket(int socket, struct sockaddr_in *server_address)
{
    int val = bind(socket, (const struct sockaddr *) server_address, sizeof(*server_address));
    if(val == -1)
    {
        close(socket);
        err(1, "Can't bind");
    }
    return val;
}
void close_socket(const int client_fd)
{
    shutdown(client_fd, 2);
    close(client_fd);
}