#include <QApplication>
#include <QtNetwork>
#include "net.h"
#include "client/chat/chat.h"
#include "client/gui/view.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    View v;
    Chat chat;

    Net net(&chat);

    return a.exec();
}
