#pragma once
#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H
#include <QObject>
#include <QTimer>
#include "servercore.h"

class networkthread:public QObject{
    Q_OBJECT
public:
    explicit networkthread(QObject *parent = nullptr);

public slots:
    void startserver(int port);
    void sendmessage(QString msg);
    void pollsocket();
    void deinitserver();

signals:
    void messagereceived(QString msg);
    void log(QString msg);

private:
    tcp_server srv1;
    QTimer* timer;
};

#endif // NETWORKTHREAD_H
