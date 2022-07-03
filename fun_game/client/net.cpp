#include "net.h"

#include <client/config.h>

#include <QDir>
#include <QFile>
#include <QIODevice>

Net::Net(Chat *chat) {
    this->chat = chat;
    
    // initialize UDP address of server
    QFile f(QDir::currentPath() + "/serveradr");
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Net(): fail to open" << f;
        exit(1);
    }
    QTextStream ts(&f);
    serv_ip = ts.readLine();
    serv_port = ts.readLine().toInt();
    sock.bind(QHostAddress(serv_ip), serv_port);

    connect(&sock, &QUdpSocket::readyRead, this, &Net::datagram_resolv);
}

// receive and resolve
void Net::datagram_resolv() {
    while(sock.hasPendingDatagrams()) {
        QNetworkDatagram datagram = sock.receiveDatagram();
        QByteArray buffer;
        sock.readDatagram(buffer.data(), buffer.size());
        qDebug() << "rec: " << buffer;

        ServerDatagram *sdg = (ServerDatagram*)buffer.data();
        // resolve the ServerDaragram
        if(sdg->type == ServerDatagram::reg) {
            // TODO: register a client   
        } else if(sdg->type == ServerDatagram::message) {
            // char->echo_message()
        } else if(sdg->type == ServerDatagram::operation) {
            // game->operate()
        }
    }
}

void Net::datagram_send(const QByteArray &data) {
    sock.writeDatagram(data, QHostAddress(serv_ip), serv_port);
    qDebug() << "message sent";
}
