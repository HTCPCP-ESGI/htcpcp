#include "../../htcpcp.h"

char *status_code_description(StatusCode code)
{
    switch(code)
    {
        case OK: return "OK";
        case BAD_REQUEST: return "Bad Request";
    }

    return NULL;
}

Response *response_new(StatusCode code, const char *body)
{
    if(!body)
        return NULL;

    Response *response = malloc(sizeof(Response));

    if(response)
    {
        response->code = code;
        response->headers = map_create();
        response->body = strdup(body);
    }

    return response;
}

void response_header(Response *response, char *key, char *value)
{
    List *values = list_new(value);
    response_headers(response, key, values);
}

void response_headers(Response *response, char *key, List *values)
{
    map_put(response->headers, key, &values, sizeof(values));
}

void response_free(Response *response)
{
    if(!response)
        return;

    map_free(&response->headers);
    free(response->body);
}
