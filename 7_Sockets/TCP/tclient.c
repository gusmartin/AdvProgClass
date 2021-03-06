/* tclient.c - simple client for TCP/IP sockets */

/* Connect to the server whose hostname or IP is given as an
   argument, at port 1234. Once connected, copy everything on
   stdin to the socket, then exit. */

#include <arpa/inet.h> // for ipv4
#include <netdb.h> // calls dns
#include <netinet/in.h> // routines that the network handles
#include <stdio.h>
#include <stdlib.h>            /* For exit() */
#include <string.h>            /* For memcpy */
#include <sys/socket.h>
#include <unistd.h>

#include "sockutil.h"          /* some utility functions */

int main(int argc, char ** argv) {
    struct sockaddr_in address;
    struct in_addr inaddr;
    struct hostent * host; //pointer that is aquired when you access the DB
    int sock;

    if (argc != 2) {
        fprintf(stderr, "only a single argument is supported\n");
        return 1;
    }

    /* If the argument can be converted to an IP, do so. If not, try
       to look it up in DNS. */
    if (inet_aton(argv[1], &inaddr))
        host = gethostbyaddr((char *) &inaddr, sizeof(inaddr), 
                               AF_INET);  // from ascii to big endian format gethostbyaddr, then return //host has hostmane, ip and aliases, with afinet you tell the that its ipv4
    else
        host = gethostbyname(argv[1]); //if ip not converted, seacrh by name

    if (!host) {
	/* We can't find an IP number */
        herror("error looking up host");
	exit(1);
    }

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) //0 is defaut protocol
        die("socket");

    address.sin_family = AF_INET; //
    address.sin_port = htons(1234); //set port, in big endian format

    /* Take the first IP address associated with this hostname */
    memcpy(&address.sin_addr, host->h_addr_list[0],
           sizeof(address.sin_addr));

    if (connect(sock, (struct sockaddr *) &address, sizeof(address)))
        die("connect");

    copyData(0, sock); //STDIN to socket, until end of file

    close(sock); 
    
    return 0;
}
