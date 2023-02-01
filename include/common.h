#ifndef __COMMON_H__
#define __COMMON_H__
// a bunch of header files and some macros

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h> //basic socket definition
#include <sys/types.h>

#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define PORT 6969
#define MAXLINE 4096

typedef struct sockaddr sockaddr;

#define check(func, msg)    \
    if ((func) == -1)       \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    }

#endif // __COMMON_H__