#include <stdio.h>
#include "../Networking/Nodes/HTTPServer.h"
// todo: retornar paginas html no desktop
char *home(struct HTTPServer *server, struct HTTPRequest *request){
    return "Home";
}
// todo: retornar paginas html no desktop
char *about(struct HTTPServer *server, struct HTTPRequest *request){
    return "About";
}
int main(){
    struct HTTPServer server = http_server_constructor();
    server.register_routes(&server, home, "/", 0);
    server.register_routes(&server, about, "/about",0);
    server.launch(&server);
}