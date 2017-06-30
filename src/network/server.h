#ifndef SERVER_H
#define SERVER_H

#define SERVER_BUFFER_SIZE 1024

typedef struct Server {
    struct sockaddr_in address;
    int socket;

    List *clients;
    HtcpcpProtocol protocol;
} Server;

Server *server_new(HtcpcpProtocol);
void server_init(Server*, Config*);
int server_listen(Server*, Config*);

void server_run(Server*);
void server_forked(Server*);
void server_multiplexed(Server*);

char *server_handle_request(Server*, Request*);

void server_free(Server*);

#endif