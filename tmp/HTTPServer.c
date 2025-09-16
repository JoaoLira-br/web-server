#include "HTTPServer.h"
#include "../Protocols/HTTPRequest.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void retrieve_page(struct HTTPRequest request, int socket);

void launch(struct Server *server){
    int addrlen = sizeof(server->address);
    long valread;
    while(1){
        printf("=== WAITING ===\n");
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&addrlen);
        char buffer[30000];
        valread = read(new_socket, buffer, 30000);
        struct HTTPRequest request = http_request_constructor(buffer);
        retrieve_page(request, new_socket);
        close(new_socket);
    }
}

void retrieve_page(struct HTTPRequest request, int socket){
    char path[30000] = {0};
    char *url = strtok(request.request_line.search(&request.request_line, "uri", sizeof("uri")), "?");
    char *vars = strtok(NULL, "\0");

    strcpy(path, "/Users/joaovictorlira/Desktop");
    if(strcmp(url, "/test") == 0){
        strcat(path, url);
    }else{
        strcat(path, "/index");
    }
    strcat(path, ".html");  // Fixed: was ",html"

    FILE *f = fopen(path, "r");  // Fixed: was FILE f = *fopen(...)
    if (f == NULL) {  // Check if file exists
        printf("Error: Could not open file %s\n", path);
        // Send 404 response
        char response[] = "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<h1>404 Not Found</h1>";
        write(socket, response, strlen(response));
        return;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (fsize <= 0) {  // Check for valid file size
        printf("Error: File %s is empty or invalid\n", path);
        fclose(f);
        char response[] = "HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n<h1>500 Server Error</h1>";
        write(socket, response, strlen(response));
        return;
    }

    char *buffer = malloc(fsize + 1);
    if (buffer == NULL) {  // Check malloc success
        printf("Error: Memory allocation failed\n");
        fclose(f);
        return;
    }

    fread(buffer, 1, fsize, f);
    buffer[fsize] = '\0';  // Null terminate
    fclose(f);

    char response[30000] = {0};
    strcpy(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    strcat(response, buffer);
    write(socket, response, strlen(response));
    
    free(buffer);  // Don't forget to free!
}