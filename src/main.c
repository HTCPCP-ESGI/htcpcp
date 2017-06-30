#include "includes.h"

Response *teapot(Request *req)
{
    return response_new(IM_A_TEAPOT, "");
}

int main(int argc, char **argv)
{
    HtcpcpProtocol protocol;
    protocol.get = teapot;
    protocol.brew = teapot;
    protocol.propfind = teapot;
    protocol.when = teapot;

    return htcpcp_init(argc, argv, protocol);
}