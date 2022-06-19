#include <QApplication>
#include "view.h"
#include "net.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Net n;
    View v;
    return a.exec();
}
