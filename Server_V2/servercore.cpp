#include "servercore.h"

servercore::servercore()
{

}


functionstate initsocket(tcp_server* srv1){
     if (srv1->serverststate ==1)
    {
        return ret_success;
    }

    srv1->sockets1 = socket(AF_INET, SOCK_STREAM, 0);
    if(srv1->sockets1<0){
        perror("Server: Socket creation failed");
        return ret_failure;
    }

    memset (&srv1->s1addr, 0, sizeof(srv1->s1addr));
    srv1->s1addr.sin_family = AF_INET;
    srv1->s1addr.sin_port = htons(srv1->PORT);
    srv1->s1addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(srv1->sockets1, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket
    if (bind(srv1->sockets1, (struct sockaddr*)&srv1->s1addr, sizeof(srv1->s1addr)) < 0) {
        perror("bind");
        printf("Server: Bind failed");
        close(srv1->sockets1);
        return ret_failure;
    }

    // Listen for connections
            if (listen(srv1->sockets1, 3) < 0) {
                perror("Server: Listen failed");
                close(srv1->sockets1);
                return ret_failure;
            }
    srv1->serverststate = 1;
    return ret_success;
}

functionstate saccept(tcp_server* srv1){
    srv1->s2addr_len = sizeof(srv1->s2addr);
    srv1->sockets2 = accept(srv1->sockets1, (struct sockaddr* )&srv1->s2addr, &srv1->s2addr_len);
    if (srv1->sockets2 < 0) {
        perror("Server: Accept failed");
        close(srv1->sockets1);
        return ret_failure;
    }
    srv1->serverststate = 1;
    srv1->client_connected = true;
    printf("Server: Connected to client Successfully1!\n");
    return ret_success;
}

functionstate ssend(tcp_server* srv1){
    ssize_t total = 0;
    ssize_t messsize = srv1->mess_to_send.size();
    while(total < messsize){
        ssize_t sent = send(srv1->sockets2, srv1->mess_to_send.data() + total, srv1->mess_to_send.size() - total, 0);
        if(sent<=0){
            perror("Server: Send failed");
            return ret_failure;
        }
        total += sent;
    }
    std::cout<<"Server: Sent "<<total<<" bytes\n";
    return ret_success;
}

functionstate srecv(tcp_server* srv1){
    req rr;
    if (srv1->sockets2 < 0) {
            printf("Server: No client connected\n");
            return ret_failure;
        }
    //recieve
    srv1->mess_to_recv.clear();
    char buffer[10240 + 1];
    rr.recv = recv(srv1->sockets2, buffer, sizeof(buffer)-1, 0);
    if (rr.recv == 0) {
        printf("Server: Client disconnected\n");
        return ret_failure;
    }
    if (rr.recv < 0) {
        perror("Server: Receive failed");
        return ret_failure;
    }
    if (rr.recv > 0) {
        buffer[rr.recv] = '\0'; // Add the null terminator

    }
    printf("Recieved message from client: %s\n", buffer);
    srv1->mess_to_recv.assign(buffer, rr.recv);
    return ret_success;
}

functionstate deinit(tcp_server* srv1){
    if (srv1->sockets2 >= 0) {
            close(srv1->sockets2);
            srv1->sockets2 = -1;
        }
        if (srv1->sockets1 >= 0) {
            close(srv1->sockets1);
            srv1->sockets1 = -1;
        }
        srv1->serverststate = 0;
        srv1->client_connected = false;
        printf("Server: Sockets closed\n");
        return ret_success;
}
