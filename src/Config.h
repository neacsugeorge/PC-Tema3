#include "Connection.h"

#ifndef CONFIG
#define CONFIG

#define DEFAULT_CONFIG_FILE "dns_servers.conf"

void loadConfig(Connection * con, char * filename);

#endif