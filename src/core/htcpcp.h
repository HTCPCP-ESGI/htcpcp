#ifndef HTCPCP_H
#define HTCPCP_H

typedef struct HtcpcpProtocol {
    Response *(*get)(Request*);
    Response *(*brew)(Request*);
    Response *(*propfind)(Request*);
    Response *(*when)(Request*);
} HtcpcpProtocol;

#endif