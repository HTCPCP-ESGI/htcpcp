#include "../includes.h"

#define HTCPCP_OPTS "da:p:m:r:b:"

Config *config_new(void)
{
    Config *config = malloc(sizeof(Config));

    if(config)
    {
        config->is_server = 0;
        config->address = NULL;
        config->port = 0;
        config->connection_queue_length = DEFAULT_CONNECTION_QUEUE_LENGTH;

        config->method = NULL;
        config->resource = NULL;
        config->body = DEFAULT_BODY;
    }

    return config;
}

int parse_opts(Config *config, int argc, char **argv)
{
    char opt;

    if(!config || argc < 2 || !argv)
        return 0;

    while((opt = getopt(argc, argv, HTCPCP_OPTS)) != -1)
    {
        switch(opt)
        {
            case 'a':
                config->address = malloc(strlen(optarg) + 1);
                sprintf(config->address, "%s", optarg);
                break;

            case 'p': {
                int port = atoi(optarg);
                if(port <= 0 || port > 65535)
                {
                    fprintf(stderr, "[-] Port value cannot be lower or equals to 0 nor greater than 65535. Provided value is: %d\n", port);
                    return 0;
                }

                config->port = (unsigned short)port;
                break;
            }

            case 'd':
                config->is_server = 1;
                break;

            case 'm':
                config->method = malloc(strlen(optarg) + 1);
                sprintf(config->method, "%s", optarg);
                break;

            case 'r':
                config->resource = malloc(strlen(optarg) + 1);
                sprintf(config->resource, "%s", optarg);
                break;

            case 'b':
                config->body = malloc(strlen(optarg) + 1);
                sprintf(config->body, "%s", optarg);
                break;

            case '?':
                if(optopt == 'a' || optopt == 'p')
                    fprintf(stderr, "[-] Option -%c requires an argument\n", optopt);
                else
                    fprintf(stderr, "[-] Unknown option '-%c'\n", optopt);
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
    if(config->method)
        free(config->method);
    if(config->resource)
        free(config->resource);
    free(config);
}