#include "htcpcp.h"

int main(int argc, char **argv)
{
    Config *config = config_new();

    printf("[~] Starting HTCPCP...\n");
    if(parse_opts(config, argc, argv))
    {
        Server *server = server_new();
        server_init(server, config);

        if(config->is_server)
        {
            printf("[+] Server mode\n");

            server_listen(server, config);
            server_run(server);
        }
        else
        {
            printf("[+] Client mode\n");

            Client *client = client_new();
            client_connect(client, server);
            client_run(client);
            client_free(client);
        }

        printf("[~] Cleaning resources...");
        server_free(server);
    }

    config_free(config);
    return 0;
}