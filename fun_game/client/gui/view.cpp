#include "client/gui/view.h"

View::View(){
    setFixedSize(WINDOW_W, WINDOW_H);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    show();
}
