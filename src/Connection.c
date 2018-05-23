#include "Connection.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

Connection * createConnection() {
    Connection * con = (Connection*) malloc(sizeof(Connection));
    memset(con, 0, sizeof(Connection));

    con -> servers = (char **)malloc(DEFAULT_SERVERS_SIZE * sizeof(char*));
    con -> max_servers = DEFAULT_SERVERS_SIZE;

    con -> server_id = -1;
    con -> fd = socket(AF_INET, SOCK_STREAM, 0);

    return con;
}

void addServer(Connection * con, char * server) {
    if (con -> length == con -> max_servers) {
        con -> max_servers *= 2;
        con -> servers = (char **)realloc(
            con -> servers,
            con -> max_servers * sizeof(char *)
        );
    }

    con -> servers[con -> length++] = strdup(server);
}

void sendQuery(Connection * con, char * query, int size) {
    if (con -> server_id == -1) {
        con -> server_id = 0;

        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(DEFAULT_PORT);
        inet_pton(AF_INET, con -> servers[con -> server_id], &(address.sin_addr));

        socklen_t address_len = sizeof(address);
        while (connect(
            con -> fd,
            (const struct sockaddr *)(&address),
            address_len
        ) == -1) {
            if (con -> server_id == con -> length - 1) {
                perror("I'm so lonely, no one responded");
                exit(-1);
            }

            con -> server_id++;
            inet_pton(AF_INET, con -> servers[con -> server_id], &(address.sin_addr));
        }
    }

    send(con -> fd, query, size, 0);
}

char * getResponse(Connection * con, int * len) {
    if (con -> server_id == -1) {
        return NULL;
    }

    char * response = (char *)malloc(BUFFER_LENGTH);
    memset(response, 0, BUFFER_LENGTH);

    int bytes_received = recv(con -> fd, response, BUFFER_LENGTH, 0);

    if (bytes_received <= 0) {
        perror("Server closed the connection");
        exit(-1);
    }

    *len = bytes_received;
    return response;
}

void printConnection(Connection * con) {
    puts("---------------------------------");
    puts("           Connection");
    puts("---------------------------------");
    printf("Servers: %d\nMax Servers: %d\n", con -> length, con -> max_servers);
    printf("Server ID: %d\n", con -> server_id);
    puts("---------------------------------");
    int i = 0;
    for (; i < con -> length; i++) {
        printf("Server IP: %s\n", con -> servers[i]);
    }
    puts("---------------------------------");
}