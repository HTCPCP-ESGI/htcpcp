#include "../includes.h"

int htcpcp_init(int argc, char **argv, HtcpcpProtocol protocol)
{
    Config *config = config_new();

    printf("[~] Starting HTCPCP...\n");
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
        printf("[+] Server mode\n");

        if(server_listen(server, config))
        {
            server_run(server);
        }
    }
    else
    {
        printf("[+] Client mode\n");

        Client *client = client_new();
        client_connect(client, server);
        client_run(client);
        client_free(client);
    }

    printf("[~] Cleaning resources...\n");
    server_free(server);
}