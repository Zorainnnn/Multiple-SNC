#ifndef SERVERCORE_H
#define SERVERCORE_H

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


class servercore
{
public:
    servercore();
};

#define MAX_MESSAGE_SIZE 1460

typedef enum{
    ret_success = 0,
    ret_failure = -1,
}functionstate;

struct packet{
    int id;
    char data[MAX_MESSAGE_SIZE];
};

struct req{
    int recv, sent;
};

struct tcp_server{
    int sockets1 = -1;
    int sockets2 = -1;
    int serverststate = 0;
    char buffer[MAX_MESSAGE_SIZE];
    struct sockaddr_in s1addr, s2addr;
    socklen_t s2addr_len;
    std::string mess_to_send;
    std::string mess_to_recv;
    bool client_connected;
    ssize_t PORT;
};

functionstate initsocket(struct tcp_server* server);
functionstate saccept(struct tcp_server* server);
functionstate ssend(struct tcp_server* server);
functionstate srecv(struct tcp_server* server);
functionstate deinit(struct tcp_server* server);

#endif // SERVERCORE_H
