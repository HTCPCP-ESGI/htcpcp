#ifndef SERVER_H
#define SERVER_H

#define SERVER_BUFFER_SIZE 1024

typedef struct Server {
    struct sockaddr_in address;
    int socket;

    List *clients;
} Server;

Server *server_new(void);
void server_init(Server*, Config*);
int server_listen(Server*, Config*);

void server_run(Server*);
void server_forked(Server*);
void server_multiplexed(Server*);

void server_free(Server*);

#endif