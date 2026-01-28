#include "clientcore.h"

clientcore::clientcore()
{

}

functionstate initsocket(tcp_client* cli1){
//create socket
    cli1->opt = 1;
    if (cli1->clienttstate == 1) {
            return cret_success;  // Already initialized
        }
    //configure socket
        cli1->socketc1 = socket(AF_INET, SOCK_STREAM, 0);
            if ( cli1->socketc1 < 0) {
                printf("Client: Socket Creation Failed");
                perror("socket");
                exit(0);
                return cret_failure;
            }
            if (setsockopt(cli1->socketc1, SOL_SOCKET, SO_REUSEADDR, &cli1->opt, sizeof(cli1->opt)) < 0) {
                perror("setsockopt");
                close(cli1->socketc1);
                exit(0);
                return cret_success;
            }
        cli1->c1addr_len = sizeof(cli1->c1addr);
        memset(&cli1->c1addr, 0, cli1->c1addr_len);
        cli1->c1addr.sin_family = AF_INET;
        cli1->c1addr.sin_port = htons(cli1->PORT);
        inet_pton(AF_INET, "127.0.0.1", &cli1->c1addr.sin_addr);
        int connection_status = connect(cli1->socketc1, (struct sockaddr *)&cli1->c1addr, cli1->c1addr_len);

        setsockopt(cli1->socketc1, SOL_SOCKET, SO_REUSEADDR, &cli1->opt, sizeof(cli1->opt));


        if (connection_status == -1) {
                printf("Client: Connection failed\n");
                perror("connect");
                close(cli1->socketc1);
                exit(0);
                return cret_failure;
            }

        printf("Client: Connected to server successfully!\n");
        cli1->clienttstate = 1;
        cli1->server_connected = 1;
    return cret_success;
}

functionstate csend(tcp_client* cli1){
    if (cli1->socketc1 < 0 || cli1->server_connected != 1) {
            printf("Client: Not connected\n");
            return cret_failure;
        }
    int wrote =  write(cli1->socketc1, cli1->mess_to_send.data(), cli1->mess_to_send.size());
    if(wrote<0){
        perror("Client: Send failed");
        return cret_failure;
    }
    std::cout<<"Client: Sent "<<wrote<<" bytes\n";
    return cret_success;
}

functionstate crecv(tcp_client* cli1){
    int byterecv;
    if (cli1->socketc1 < 0 || cli1->server_connected != 1) {
           printf("Client: No client connected\n");
           return cret_failure;
       }
    char buffer[4096];
    byterecv = recv(cli1->socketc1, buffer, sizeof(buffer), 0);
    if (byterecv == 0) {
        printf("Client: Server disconnected\n");
        return cret_failure;
    }
    if (byterecv < 0) {
        perror("Client: Receive failed");
        return cret_failure;
    }
    if (byterecv > 0) {
        buffer[byterecv] = '\0'; // Add the null terminator

    }
    printf("Recieved message from server: %s\n", buffer);
    cli1->mess_to_recv.assign(buffer, byterecv);
    return cret_success;
}

functionstate deinit(tcp_client* cli1){
    if (cli1->socketc1 >= 0) {
            close(cli1->socketc1);
            cli1->socketc1 = -1;
        }
    cli1->clienttstate = 0;
    printf("Client: Socket closed.\n");
    return cret_success;
}
