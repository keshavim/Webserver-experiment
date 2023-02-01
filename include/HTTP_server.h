#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__
#include "common.h"
#include "Binary_tree.h"

typedef struct HTTP_Server{
    int32_t fd;
    int32_t port;
} HTTP_Server;

void server_init(HTTP_Server *self, int32_t port);

void server_handle_connection(int32_t fd, BinTree *router);



#endif // __HTTP_SERVER_H__