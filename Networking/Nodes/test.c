#include <stdio.h>
#include "HTTPServer.h"

int main(){
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 20, launch);
    server.launch(&server);
}