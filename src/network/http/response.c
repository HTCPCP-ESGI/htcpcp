#include "../../includes.h"

char *status_code_description(StatusCode code)
{
    switch(code)
    {
        case OK: return "200 OK";
        case NOT_ACCEPTABLE: return "406 Not Acceptable";
        case IM_A_TEAPOT: return "418 I'm a teapot";
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

char *response_serialize(Response *response)
{
    char *status = status_code_description(response->code);
    size_t size = strlen(status) + 2 /* \n\n */ + strlen(response->body) + 2 /* \n\0 */;

    char *serialized = malloc(size);
    sprintf(serialized, "%s\n\n%s\n", status, response->body);

    return serialized;
}

void response_free(Response *response)
{
    if(!response)
        return;

    map_free(&response->headers);
    free(response->body);
}
