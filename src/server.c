#include "htcpcp.h"

Server *server_new(void)
{
    Server *server = malloc(sizeof(Server));

    if(server)
    {
        // bzero is a deprecated BSD function, we should use memset instead
        memset(&server->address, 0, sizeof(server->address));
        server->socket = 0;
    }

    return server;
}

int server_init(Server *server, Config *config)
{
    // Init the server address
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = inet_addr(config->address);
    server->address.sin_port = htons(config->port);

    // Init the server socket
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server->socket == -1)
    {
        fprintf(stderr, "[-] socket() failed\n");
        return 0;
    }

    // Bind the address to the socket
    int binding = bind(server->socket, (struct sockaddr*)&server->address, sizeof(server->address));
    if(binding == -1)
    {
        fprintf(stderr, "[-] bind() failed\n");
        return 0;
    }

    // Set the socket in passive mode, ready to accept connections
    int listening = listen(server->socket, config->connection_queue_length);
    if(listening == -1)
    {
        fprintf(stderr, "[-] listen() failed\n");
        return 0;
    }

    return 1;
}

void server_run(Server *server)
{
    // TODO
}

void server_free(Server *server)
{
    close(server->socket);
    free(server);
}