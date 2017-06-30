#include "../includes.h"

Client *client_new(void)
{
    Client *client = malloc(sizeof(Client));

    if(client)
    {
        memset(&client->address, 0, sizeof(struct sockaddr));
        client->addr_len = 0;
        client->socket = 0;
        memset(client->buffer, 0, CLIENT_BUFFER_SIZE);
    }

    return client;
}

int client_connect(Client *client, Server *server)
{
    client->socket = socket(AF_INET, SOCK_STREAM, 0);

    int connected = connect(client->socket, (struct sockaddr*) &server->address, sizeof(server->address));
    if(connected == -1)
    {
        fprintf(stderr, "[-] connect() failed\n");
        return 0;
    }

    return 1;
}

void client_run(Client *client)
{
    fgets(client->buffer, CLIENT_BUFFER_SIZE, stdin);
    printf("[+] Input: %s", client->buffer);
    write(client->socket, client->buffer, strlen(client->buffer) + 1);

    read(client->socket, client->buffer, CLIENT_BUFFER_SIZE);
    printf("[+] Server says > %s", client->buffer);
}

void client_free(Client *client)
{
    free(client);
}