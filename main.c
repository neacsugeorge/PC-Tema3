#include <stdio.h>
#include "src/Config.h"
#include "src/Connection.h"
#include "src/Structures.h"

int main () {
    Connection * con = createConnection();
    loadConfig(con, DEFAULT_CONFIG_FILE);
    printConnection(con);

    return 0;
}