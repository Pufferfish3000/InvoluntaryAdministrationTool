#include <bearssl.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "agent.h"
#include "common.h"

// will be replaced later
unsigned char cert[] = "";
unsigned char priv_key[] = "";
unsigned char ca[] = "";

int CreateConSock(char* address, char* port)
{
    int sock = -1;
    int err = 0;

    struct addrinfo hints = {0};
    struct addrinfo* result = NULL;
    struct addrinfo* rp = NULL;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (NULL == address)
    {
        DPRINTF("Address cannot be NULL");
        goto end;
    }
    if (NULL == port)
    {
        DPRINTF("Port cannot be NULL");
        goto end;
    }

    err = getaddrinfo(address, port, &hints, &result);

    if (err != 0)
    {
        DPRINTF("getaddrinfo: %s", gai_strerror(err));
        goto clean;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock == -1)
        {
            continue;
        }

        if (-1 != connect(sock, rp->ai_addr, rp->ai_addrlen))
        {
            break;
        }

        close(sock);
    }

clean:
    freeaddrinfo(result);

    if (sock == -1)
    {
        DPRINTF("Could not connect to %s:%s", address, port);
        return -1;
    }

    DPRINTF("Connected to %s:%s", address, port);

end:
    return sock;
}

int CreateTlsConSock(char* address, char* port) {}
