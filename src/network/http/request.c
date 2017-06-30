#include "../../includes.h"

int parse_request(Request*, const char*);
int parse_method(Request*, char*);
int parse_header(Request*, char*);

Request *request_new(const char *raw)
{
    Request *request = malloc(sizeof(Request));

    if(request)
    {
        request->method = NULL;
        request->resource = NULL;
        request->headers = map_create();
        request->body = NULL;

        if(!parse_request(request, raw))
        {
            fprintf(stderr, "[-] Failed to parse request\n");
            return NULL;
        }
    }

    return request;
}

int parse_request(Request *request, const char *raw)
{
    if(!request || !raw)
        return 0;

    int method_parsed = 0;

    char *str = strdup(raw);
    char *index = NULL;

    while((index = strpbrk(str, "\n")) != NULL)
    {
        // If double \n, break and save body
        if(str == index)
        {
            str++;
            break;
        }

        // Copy current line
        int size = index - str;
        char *line = malloc(size + 1);
        strncpy(line, str, size);

        // Parse method & resource
        if(!method_parsed)
        {
            if(!parse_method(request, line))
                return 0;

            method_parsed = 1;
        }
        // Parse headers
        else
            parse_header(request, line);

        str = index + 1;
    }

    if(str)
    {
        request->body = strdup(str);
    }

    return 1;
}

int parse_method(Request *request, char *line)
{
    if(!request || !line)
        return 0;

    char *index = strpbrk(line, " ");

    if(!index)
        return 0;

    int size = index - line;
    request->method = malloc(size + 1);
    strncpy(request->method, line, size);

    line = index + 1;
    size = strlen(line);
    request->resource = malloc(size + 1);
    strncpy(request->resource, line, size);

    return 1;
}

int parse_header(Request *request, char *line)
{
    if(!request || !line)
        return 0;

    char *index = strpbrk(line, ":");

    if(!index)
        return 0;

    // Header key
    int size = index - line;
    char *key = malloc(size + 1);
    strncpy(key, line, size);

    // Escape ': '
    line = index + 2;

    // Parse header values
    List *values = NULL;
    while((index = strpbrk(line, ",")) != NULL)
    {
        size = index - line;
        char *value = malloc(size + 1);
        strncpy(value, line, size);

        list_add(&values, value);
        // Escape ', '
        line = index + 2;
    }

    // Only one value OR last value of the list
    if(line)
    {
        list_add(&values, strdup(line));
    }

    // Add the (key, values) header to the request's map
    map_put(request->headers, key, &values, sizeof(values));

    return 1;
}

void request_free(Request *request)
{
    if(!request)
        return;

    free(request->method);
    free(request->resource);
    map_free(&request->headers);
    free(request->body);
}