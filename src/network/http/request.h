#ifndef REQUEST_H
#define REQUEST_H

typedef struct Request {
    char *method;
    char *resource;
    HashMap *headers;
    char *body;
} Request;

Request *request_new(const char*);
void request_free(Request*);

#endif