#include "../includes.h"

int htcpcp_init(int argc, char **argv, HtcpcpProtocol protocol)
{
    Config *config = config_new();

    if(parse_opts(config, argc, argv))
    {
        htcpcp_run(protocol, config);
    }

    config_free(config);

    return 0;
}

void htcpcp_run(HtcpcpProtocol protocol, Config *config)
{
    Server *server = server_new(protocol);
    server_init(server, config);

    if(config->is_server)
    {
        printf("[+] Server listening on port %d\n", config->port);

        if(server_listen(server, config))
        {
            server_run(server);
        }
    }
    else
    {
        if(config->method && config->resource)
        {
            Client *client = client_new();
            if(client_connect(client, server))
            {
                client_run(client, config);
                client_free(client);
            }
        }
        else
        {
            fprintf(stderr, "[-] You have to specify a method (-m) and resource (-r)\n");
        }
    }

    server_free(server);
}