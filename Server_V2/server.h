#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include "networkthread.h"
#include <QTextEdit>
#include <QPushButton>

class networkthread;
class QThread;

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

signals:
    void sendmessage(QString msg);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Server *ui;
    QThread *netthread;
    networkthread *worker;
};
#endif // SERVER_H

