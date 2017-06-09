#ifndef HTTP_H
#define HTTP_H

typedef struct Response {
    unsigned short code;
    HashMap *headers;
    char *body;
} Response;

#endif