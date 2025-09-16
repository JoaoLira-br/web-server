#include "Server.h"
#include <string.h> // para memset
#include <stdio.h>
#include <stdlib.h>
struct Server server_constructor(int domain, int service, int protocol, u_long interface, 
    int port, int backlog) {
    
    struct Server server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface    ;
    server.port = port;
    server.backlog = backlog;
    server.address.sin_family = domain;
    // h to network convert integer port to bytes that refer to network port
    server.address.sin_port = htons(port);
    // h to network convert long interface to bytes that refer to network port
    server.address.sin_addr.s_addr = htonl(interface);
    // this will return us an address of where this socket is located
    server.socket = socket(domain, service, protocol);
    if (server.socket == -1){
        perror("Failed to connect socket...\n");
        // exit com 1 representa falha
        exit(1);
    }
    // In your server_constructor function
    printf("DEBUG: About to set socket options...\n");
    int opt = 1;
    if (setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Failed to set socket options...\n");
        exit(1);
    }
    printf("DEBUG: Attempting to bind to port %d\n", ntohs(server.address.sin_port));
    if(bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address)) < 0){
        perror("Failed to bind socket...\n");
        exit(1);
    }
    if (listen(server.socket, server.backlog) < 0) {
        perror("Failed to start listening...\n");
        exit(1);
    };  
 

    return server;
}
