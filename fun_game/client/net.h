#pragma once
#include "client/chat/chat.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "client/protocol.h"

// client
class Net : public QObject{
    Q_OBJECT
   public:
    Net(Chat *chat);

   private:
    QUdpSocket sock;
    QString serv_ip;
    int serv_port;
    
    Chat *chat;
    // Game *game;

   private slots:
    void datagram_resolv();
    void datagram_send(const QByteArray&);
};
