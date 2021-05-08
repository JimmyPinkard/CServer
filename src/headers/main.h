#ifndef CSERVER_MAIN_H
#define CSERVER_MAIN_H

//Used to accept the request
int main();
//Function name is a lie, it's reading the whole header, but we're only using the endpoint and returning the file name
const char *get_endpoint(const int fd);
//Used to respond to the request
void route(const int client_fd);

#endif //CSERVER_MAIN_H
