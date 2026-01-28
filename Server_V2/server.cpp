#include "server.h"
#include "ui_server.h"
#include "networkthread.h"

#include <QThread>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    netthread = new QThread(this);
    worker = new networkthread();

    worker->moveToThread(netthread);


    //Start server when thread starts
    connect(netthread, &QThread::started,
            worker, [=]() {
                worker->startserver(8080);   // choose port
            });

    //GUI to Network
    connect(this, &Server::sendmessage,
            worker, &networkthread::sendmessage);

    //Network to GUI
    connect(worker, &networkthread::messagereceived,
            this, [this](QString msg) {
                ui->recvmess->append(msg);
            });

    //Button click to emit sendMessage
    connect(ui->sendbutton, &QPushButton::clicked,
            this, [this]() {
                QString msg = ui->sendmess->toPlainText();
                if (msg.isEmpty()) return;

                emit sendmessage(msg);
                ui->sendmess->clear();
            });
    netthread->start();
}

Server::~Server()
{
    netthread->quit();
    netthread->wait();
    worker->deinitserver();
    delete worker;
    delete ui;}


void Server::on_pushButton_2_clicked()
{
    ui->recvmess->clear();
}

