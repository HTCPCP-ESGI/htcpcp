#ifndef REQUEST_H
#define REQUEST_H

typedef struct Request {
    char *method;
    char *resource;
    HashMap *headers;
    char *body;
} Request;

Request *request_raw(const char*, const char*, const char*, HashMap*);
Request *request_new(const char*);
char *request_serialize(Request*);
void request_free(Request*);

#endif