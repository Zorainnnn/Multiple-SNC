#include "networkthread.h"

networkthread::networkthread(QObject *parent)
    : QObject(parent)
{

}

void networkthread::startserver(int port){
    srv1.PORT = port;
    if(initsocket(&srv1) != ret_success){
        perror("Initialization Failed.");
        exit(0);
    }
    if(saccept(&srv1) != ret_success){
        perror("Initialization Failed.");
        exit(0);
    }
    emit log("Client Connected");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &networkthread::pollsocket);
    timer->start(10);
}


void networkthread::sendmessage(QString msg){
    srv1.mess_to_send = msg.toStdString();
    ssend(&srv1);
}

void networkthread::pollsocket(){
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(srv1.sockets2, &readfds);

    int nfds = srv1.sockets2 + 1;
    timeval tv{0, 0};
    int ready = select(nfds, &readfds, nullptr, nullptr, &tv);

    if (ready > 0 && FD_ISSET(srv1.sockets2, &readfds)) {
        if (srecv(&srv1) != ret_success)
                    return;
        emit messagereceived(
                   QString::fromUtf8(srv1.mess_to_recv.data(), srv1.mess_to_recv.size()));
        srv1.mess_to_recv.clear();
    }
}

void networkthread::deinitserver(){
    deinit(&srv1);
}
