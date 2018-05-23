
#ifndef CONNECTION
#define CONNECTION

#define DEFAULT_SERVERS_SIZE 2
#define DEFAULT_PORT 53

#define BUFFER_LENGTH 1542

typedef struct {
    char ** servers;
    int length;
    int max_servers;
    int server_id;
    int fd;
} Connection;

Connection * createConnection();
void addServer(Connection * con, char * server);
void sendQuery(Connection * con, char * query);
char * getResponse(Connection * con);
void printConnection(Connection * con);

#endif