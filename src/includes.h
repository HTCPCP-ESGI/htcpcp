#ifndef INCLUDES_H
#define INCLUDES_H

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

#include "collections/list/List.h"
#include "collections/map/HashMapEntry.h"
#include "collections/map/HashMap.h"

#include "config/config.h"

#include "network/http/response.h"
#include "network/http/request.h"
#include "core/htcpcp.h"

#include "network/client.h"
#include "network/server.h"

#include "core/lib.h"

#endif