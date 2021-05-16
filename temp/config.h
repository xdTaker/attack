#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <linux/tcp.h>

void setIf(int sock, const char *ifname) {
    struct ifreq interface;
    /* Management net interface name */
    
    /* Acquire socket here ... */
    
    strncpy(interface.ifr_ifrn.ifrn_name, ifname, IFNAMSIZ);
    if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, \
            (char *)&interface, sizeof(interface)) < 0) {
        perror("SO_BINDTODEVICE failed");
        /* Deal with error... */
    }
}