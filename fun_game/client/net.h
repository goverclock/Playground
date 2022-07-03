#pragma once

#include <QUdpSocket>

// client
class Net {
   public:
    Net();

   private:
    QUdpSocket serv_adr;

};
