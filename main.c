#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "src/Config.h"
#include "src/Connection.h"
#include "src/Structures.h"

int main (int argc, char *argv[]) {
    Connection * con = createConnection();
    loadConfig(con, DEFAULT_CONFIG_FILE);
    printConnection(con);

    int len = 0;
    char * query = createQuery(argv[1], argv[2], &len);

    sendQuery(con, query, len);
    char * answer = getResponse(con, &len);


    return 0;
}