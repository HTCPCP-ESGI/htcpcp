#ifndef CONFIG_H
#define CONFIG_H

typedef struct Config {
    int is_server;

    char *address;
    int port;
} Config;

Config *config_new();
int parse_opts(Config*, int, char**);
void config_free(Config*);

#endif