#include "client.h"
#include "ui_client.h"
#include "networkthread.h"
#include <QThread>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    netthread = new QThread(this);
    thread = new networkthread();
    //create a new Qthread with this(GUI) as its parent.
    thread -> moveToThread(netthread);
    //this makes all slots execute within netthread

    //This is network thread which starts when the client gui starts
    connect(netthread, &QThread::started, thread, [=](){
        thread->startclient(8080);
    });

    //this block send mess written in gui to netthread
    connect(this, &Client::sendmessage, thread, &networkthread::sendmessage);

    //this blocks receives message from network thread
    connect(thread, &networkthread::messagereceived, this, [this](QString msg){
        ui->recvmess->append(msg);
    });


    //when button clicked, it emits sendmessage
    connect(ui->sendbutton, &QPushButton::clicked, this, [this](){
        QString msg = ui->sendmess->toPlainText();
        if (msg.isEmpty()) return;

        emit sendmessage(msg);
        ui->sendmess->clear();
    });
    netthread->start();
}

Client::~Client()
{
    netthread->quit();
    netthread->wait();
    thread->deinitsocket();
    delete thread;
    delete ui;
}


void Client::on_pushButton_2_clicked()
{
    ui->recvmess->clear();
}

