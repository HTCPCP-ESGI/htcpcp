#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_CONNECTION_QUEUE_LENGTH 10
#define DEFAULT_BODY ""

typedef struct Config {
    int is_server;

    char *address;
    unsigned short port;
    unsigned short connection_queue_length;

    char *method;
    char *resource;
    char *body;
} Config;

Config *config_new(void);
int parse_opts(Config*, int, char**);
void config_free(Config*);

#endif