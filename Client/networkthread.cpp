#include "networkthread.h"

networkthread::networkthread(QObject *parent):QObject(parent)
{

}


void networkthread::startclient(int port){
    cli1.PORT = port;
    if(initsocket(&cli1) != cret_success){
        perror("Initialization Failed.");
        exit(0);
    }
    emit log("Connected to Server.");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &networkthread::pollsocket);
    timer->start(10);
}

void networkthread::sendmessage(QString msg){
    cli1.mess_to_send = msg.toStdString();
    csend(&cli1);
}

void networkthread::pollsocket(){
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(cli1.socketc1, &readfds);

    int nfds = cli1.socketc1+ 1;
    timeval tv{0, 0};
    int ready = select(nfds, &readfds, nullptr, nullptr, &tv);

    if (ready > 0 && FD_ISSET(cli1.socketc1, &readfds)) {
        if (crecv(&cli1) != cret_success)
                    return;
        emit messagereceived(
                   QString::fromUtf8(cli1.mess_to_recv.data(), cli1.mess_to_recv.size()));
        cli1.mess_to_recv.clear();
    }
}

void networkthread::deinitsocket(){
    deinit(&cli1);
}
