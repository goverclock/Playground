#pragma once

#include <QObject>
#include <QGraphicsRectItem>

class Tank;

class Health: public QObject, public QGraphicsRectItem {
    Q_OBJECT
   public:
    Health(Tank *par);

    Tank *parent;
    const int max_health = 600;
    int cur_health = 600;
   
   public slots:
    void health_reposition();
    void health_decrease(int);
    void health_increase(int);
};
