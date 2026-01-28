#pragma once
#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H
#include <QObject>
#include <QTimer>
#include <QString>
#include <clientcore.h>

class networkthread:public QObject
{
    Q_OBJECT
public:
    explicit networkthread(QObject *parent = nullptr);

public slots:
    void startclient(int port);
    void sendmessage(QString msg);
    void pollsocket();
    void deinitsocket();

signals:
    void messagereceived(QString msg);
    void log(QString msg);

private:
    tcp_client cli1;
    QTimer* timer;
};

#endif // NETWORKTHREAD_H
