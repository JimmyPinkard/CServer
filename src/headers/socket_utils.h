#ifndef CSERVER_SOCKET_UTILS_H
#define CSERVER_SOCKET_UTILS_H

//opens a socket and does error checking
int open_socket(int domain, int type, int protocol);
//sets the server_address information
void set_server(struct sockaddr_in *server_address, int port);
//binds and error checks the socket
int bind_socket(int socket, struct sockaddr_in *server_address);
//Shutsdown and closes socket
void close_socket(const int client_fd);
#endif
