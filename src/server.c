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

void server_init(Server *server, Config *config)
{
    // Init the server address
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = inet_addr(config->address);
    server->address.sin_port = htons(config->port);
}

int server_listen(Server *server, Config *config)
{
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
    while(1)
    {
        Client *client = client_new();
        client->socket = accept(server->socket, &client->address, &client->addr_len);

        int is_parent = fork();

        if(is_parent)
            continue;

        while(1)
        {
            read(client->socket, client->buffer, CLIENT_BUFFER_SIZE);

            // Cleanup client on "exit"
            if(!strcmp(client->buffer, "exit\n"))
            {
                client_free(client);
                exit(0);
            }

            printf("Client says > %s\n", client->buffer);
            write(client->socket, client->buffer, strlen(client->buffer) + 1);
        }
    }
}

void server_free(Server *server)
{
    if(server->socket)
        close(server->socket);
    free(server);
}