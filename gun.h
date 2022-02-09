#pragma once
#include <QGraphicsRectItem>
#include <QObject>

class Tank;

class Gun : public QObject, public QGraphicsRectItem {
    Q_OBJECT
   public:
    Gun(Tank *par);

    Tank *parent;
    int gun_higth;
    int gun_width;
    int range = 300;
    int fire_gap = 150;
    int fire_load;          // initialized as fire_gap
    int rotate_rate;
    bool locked = false;    // locked at the target
    bool steady;

   public slots:
    void rotate_lock_to_target();    // lock
    void rotate_lock_reset();        // unlock
    void fire();
    void load();
};
