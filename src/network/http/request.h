#ifndef HTTP_H
#define HTTP_H

typedef struct Request {
    char *method;
    char *resource;
    HashMap *headers;
    char *body;
} Request;

Request *request_new(const char*);

#endif