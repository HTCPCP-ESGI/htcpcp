#ifndef SERVER_H
#define SERVER_H

#define SERVER_BUFFER_SIZE 1024

typedef struct Server {
    struct sockaddr_in address;
    int socket;
} Server;

Server *server_new(void);
int server_init(Server*, Config*);
void server_run(Server*);
void server_free(Server*);

#endif