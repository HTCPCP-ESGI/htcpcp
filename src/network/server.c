#include "../includes.h"

Server *server_new(HtcpcpProtocol protocol)
{
    Server *server = malloc(sizeof(Server));

    if(server)
    {
        // bzero is a deprecated BSD function, we should use memset instead
        memset(&server->address, 0, sizeof(server->address));
        server->socket = 0;

        server->clients = NULL;
        server->protocol = protocol;
    }

    return server;
}

void server_init(Server *server, Config *config)
{
    // Init the server address
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = (config->is_server) ? htons(INADDR_ANY) : inet_addr(config->address);
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
        server_forked(server);
        //server_multiplexed(server);
    }
}

void server_forked(Server *server)
{
    Client *client = client_new();
    client->socket = accept(server->socket, &client->address, &client->addr_len);

    int is_parent = fork();
    if(is_parent)
        return;

    read(client->socket, client->buffer, CLIENT_BUFFER_SIZE);
    printf("[+] Received request > %s", client->buffer);

    Request *request = request_new(client->buffer);
    char *response = server_handle_request(server, request);
    write(client->socket, response, strlen(response) + 1);

    client_free(client);
    free(response);
    exit(0);
}

void server_multiplexed(Server *server)
{
    int max_fd;
    fd_set readfs;
    unsigned int i;
    List *clients = server->clients;

    FD_ZERO(&readfs);
    FD_SET(server->socket, &readfs);
    max_fd = server->socket;

    while(clients)
    {
        printf(" +1 Client\n");
        Client *client = (Client*) clients->value;
        FD_SET(client->socket, &readfs);

        if(client->socket > max_fd)
            max_fd = client->socket;

        clients = clients->next;
    }

    printf("Before select\n");
    int res = select(max_fd + 1, &readfs, NULL, NULL, NULL);
    printf("After select\n");

    if(!res)
    {
        fprintf(stderr, "[-] select() failed\n");
        return;
    }

    if(FD_ISSET(server->socket, &readfs))
    {
        Client *client = client_new();
        client->socket = accept(server->socket, &client->address, &client->addr_len);

        list_add(&server->clients, &client);
    }

    clients = server->clients;
    for(i = 0 ; clients ; ++i)
    {
        Client *client = (Client*) clients->value;

        // TODO: server abort (core dump) on client ^C
        if(FD_ISSET(client->socket, &readfs))
        {
            int read_value = read(client->socket, client->buffer, CLIENT_BUFFER_SIZE);

            // Cleanup client on read error or "exit"
            if(read_value == -1 || !read_value || !strcmp(client->buffer, "exit\n"))
            {
                client_free(client);
                clients = clients->next;
                list_remove(&server->clients, i--);
            }
            else
            {
                printf("Client says > %s\n", client->buffer);
                write(client->socket, client->buffer, strlen(client->buffer) + 1);
                clients = clients->next;
            }
        }
        else
            clients = clients->next;
    }
}

char *server_handle_request(Server *server, Request *req)
{
    if(req)
    {
        if(req->method)
        {
            if(!strcmp(req->method, "GET"))
            {
                Response *res = server->protocol.get(req);
                return response_serialize(res);
            }
            else if(!strcmp(req->method, "BREW"))
            {
                Response *res = server->protocol.brew(req);
                return response_serialize(res);
            }
            else if(!strcmp(req->method, "PROPFIND"))
            {
                Response *res = server->protocol.propfind(req);
                return response_serialize(res);
            }
            else if(!strcmp(req->method, "WHEN"))
            {
                Response *res = server->protocol.when(req);
                return response_serialize(res);
            }
        }

        Response *res = response_new(NOT_ACCEPTABLE, "Invalid method");
        return response_serialize(res);
    }
    else
    {
        Response *res = response_new(NOT_ACCEPTABLE, "Invalid request");
        return response_serialize(res);
    }
}

void server_free(Server *server)
{
    if(server->socket)
        close(server->socket);
    free(server);
}