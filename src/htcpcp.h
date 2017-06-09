#ifndef HTCPCP_H
#define HTCPCP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <getopt.h>

#include "list/List.h"
#include "map/HashMapEntry.h"
#include "map/HashMap.h"

#include "config/config.h"

#include "network/http/request.h"
#include "network/http/response.h"
#include "network/client.h"
#include "network/server.h"

#endif