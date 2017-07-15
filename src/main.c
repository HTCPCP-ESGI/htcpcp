#include "includes.h"

Response *teapot(Request *req)
{
    return response_new(IM_A_TEAPOT, "");
}

Response *get(Request *req)
{
    return response_new(OK, "GET");
}

Response *brew(Request *req)
{
    return response_new(OK, "BREW");
}

Response *propfind(Request *req)
{
    return response_new(OK, "PROPFIND");
}

Response *when(Request *req)
{
    return response_new(OK, "WHEN");
}

int main(int argc, char **argv)
{
    HtcpcpProtocol protocol;
    protocol.get = get;
    protocol.brew = brew;
    protocol.propfind = propfind;
    protocol.when = when;

    return htcpcp_init(argc, argv, protocol);
}