#ifndef LIB_H
#define LIB_H

int htcpcp_init(int, char**, HtcpcpProtocol);
void htcpcp_run(HtcpcpProtocol, Config*);

#endif