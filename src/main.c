#include "htcpcp.h"

int main(int argc, char **argv)
{
    Config *config = config_new();

    printf("Starting HTCPCP...\n");
    if(parse_opts(config, argc, argv))
    {
        if(config->address)
            printf("Address: %s\n", config->address);
        if(config->port)
            printf("Port: %d\n", config->port);

        if(config->is_server)
            printf("Server mode\n");
        else
            printf("Client mode\n");
    }

    config_free(config);
    return 0;
}