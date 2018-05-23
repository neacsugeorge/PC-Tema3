#include "Structures.h"
#include "Connection.h"
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

dns_header_t * createHeader() {
    dns_header_t * header = (dns_header_t*)malloc(sizeof(dns_header_t));
    memset(header, 0, sizeof(dns_header_t));

    header -> id = htons((unsigned short)strlen("Gigel Frone"));
    header -> rd = 1;

    header -> qdcount = htons(1);

    return header;
}

unsigned short getType(char * type) {
    if (strcmp(type, "A") == 0) {
        return A;
    }
    else if (strcmp(type, "NS") == 0) {
        return NS;
    }
    else if (strcmp(type, "CNAME") == 0) {
        return CNAME;
    }
    else if (strcmp(type, "MX") == 0) {
        return MX;
    }
    else if (strcmp(type, "SOA") == 0) {
        return SOA;
    }
    else if (strcmp(type, "TXT") == 0) {
        return TXT;
    }
    
    return -1;
}

dns_question_t * createQuestion(char * name, char * type) {
    dns_question_t * question = (dns_question_t*)malloc(sizeof(dns_question_t));

    question -> qclass = htons(1);
    question -> qtype = htons(getType(type));

    int i = 0, len = strlen(name);
    char * ptr = strtok(name, ".");

    question -> qname = (char *)calloc(len + 1, 1);

    while (ptr != NULL) {
        question -> qname[i] = strlen(ptr);
        strcat(question -> qname, ptr);

        i += question -> qname[i] + 1;
        ptr = strtok(NULL, ".");
    }

    return question;
}

char * createQuery(char * name, char * type, int * len) {
    dns_header_t * header = createHeader();
    dns_question_t * question = createQuestion(name, type);

    char * query = (char*)calloc(BUFFER_LENGTH, 1);
    
    unsigned short index = 2;
    // Copy header
    memcpy(query + index, header, sizeof(dns_header_t));
    index += sizeof(dns_header_t);

    // Copy qname
    memcpy(query + index, question -> qname, strlen(question -> qname));
    index += strlen(question -> qname) + 1;

    // Copy qtype
    memcpy(query + index, &question -> qtype, 2);
    index += 2;

    // Copy qclass
    memcpy(query + index, &question -> qclass, 2);
    index += 2;

    // Write packet size
    unsigned short hindex = htons(index -2);
    memcpy(query, &hindex, 2);

    *len = index;
    return query;
}