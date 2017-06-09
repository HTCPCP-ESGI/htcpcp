#ifndef RESPONSE_H
#define RESPONSE_H

typedef enum {
    OK = 200,
    BAD_REQUEST = 400
} StatusCode;

char *status_code_description(StatusCode);

typedef struct Response {
    StatusCode code;
    HashMap *headers;
    char *body;
} Response;

Response *response_new(StatusCode, const char*);
void response_header(Response*, char*, char*);
void response_headers(Response*, char*, List*);
void response_free(Response*);

#endif