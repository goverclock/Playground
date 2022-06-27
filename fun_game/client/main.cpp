#include <QApplication>
#include <QtNetwork>
#include "view.h"
#include "net.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    View v;
    return a.exec();
}
