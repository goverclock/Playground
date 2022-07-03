#include "net.h"

#include <client/config.h>

#include <QDir>
#include <QFile>
#include <QIODevice>

Net::Net() {
    QFile f(QDir::currentPath() + "/serveradr");
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Net(): fail to open" << f;
        exit(1);
    }

    QTextStream ts(&f);
    auto ip = ts.readLine();
    auto port = ts.readLine();
    serv_adr.bind(QHostAddress(ip), port.toInt());
}
