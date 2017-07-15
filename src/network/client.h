#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"

#define CLIENT_BUFFER_SIZE 1024

typedef struct Client {
    struct sockaddr address;
    socklen_t addr_len;
    int socket;
    char buffer[CLIENT_BUFFER_SIZE];
} Client;

Client *client_new(void);
int client_connect(Client*, Server*);
void client_run(Client*, Config*);
void client_free(Client*);

#endif