#include "Config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void loadConfig(Connection * con, char * filename) {
    FILE * file;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Cannot open config file");
        exit(-1);
    }

    size_t size = 0;
    char * line = NULL;
    while((size = getline(&line, &size, file)) != -1) {
        size_t len = strlen(line) - 1;
        if (*line && line[len] == '\n') {
            line[len] = '\0';
        }

        if (line[0] == '#' || line[0] == 0) {
            continue;
        }

        addServer(con, line);
    }

    fclose(file);
}