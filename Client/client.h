#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <networkthread.h>
#include <QTextEdit>
#include <QPushButton>

class networkthread;
class QThread;

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

signals:
    void sendmessage(QString msg);

private slots:

    void on_pushButton_2_clicked();

private:
    Ui::Client *ui;
    QThread *netthread;
    /*netthread contains address to a seprate Qthreadobject*/
    networkthread *thread;
    /*thread is the object
     netwrok thread is the class, which contains
    the clientcore blocking code*/
};
#endif // CLIENT_H
