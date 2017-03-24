#include "htcpcp.h"

#define HTCPCP_OPTS "a:p:d"

Config *config_new()
{
    Config *config = malloc(sizeof(Config));

    if(config)
    {
        config->is_server = 0;
        config->address = NULL;
        config->port = 0;
    }

    return config;
}

int parse_opts(Config *config, int argc, char **argv)
{
    char opt;

    if(!config || argc < 1 || !argv)
        return 0;

    while((opt = getopt(argc, argv, HTCPCP_OPTS)) != -1)
    {
        switch(opt)
        {
            case 'a':
                config->address = malloc(strlen(optarg) + 1);
                sprintf(config->address, "%s", optarg);
                break;

            case 'p':
                config->port = atoi(optarg);
                break;

            case 'd':
                config->is_server = 1;
                break;

            case '?':
                if(optopt == 'a' || optopt == 'p')
                    fprintf(stderr, "Option -%c requires an argument\n", optopt);
                else
                    fprintf(stderr, "Unknown option '-%c'\n", optopt);
                return 0;

            default:
                return 0;
        }
    }

    return 1;
}

void config_free(Config *config)
{
    if(config->address)
        free(config->address);
    free(config);
}