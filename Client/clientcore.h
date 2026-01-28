#ifndef CLIENTCORE_H
#define CLIENTCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_MESSAGE_SIZE 1460

typedef enum{
    cret_success = 0,
    cret_failure = -1,
}functionstate;

struct packet{
    int id;
    char data[MAX_MESSAGE_SIZE];
};

struct req{
    int recv, sent;
};

struct tcp_client{
    int socketc1 = -1;
    int clienttstate = 0;
    int opt = 1;
    char buffer[MAX_MESSAGE_SIZE];
    struct sockaddr_in c1addr;
    socklen_t c1addr_len;
    std::string mess_to_send;
    std::string mess_to_recv;
    bool server_connected;
    ssize_t PORT;
};

functionstate initsocket(struct tcp_client* client);
functionstate caccept(struct tcp_client* client);
functionstate csend(struct tcp_client* client);
functionstate crecv(struct tcp_client* client);
functionstate deinit(struct tcp_client* client);


class clientcore
{
public:
    clientcore();
};

#endif // CLIENTCORE_H
