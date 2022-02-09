#pragma once
#include <QGraphicsRectItem>
#include <QObject>
#include <QPointF>
#include <QtMultimedia/QMediaPlayer>
#include <QSound>

#include "base.h"
#include "gun.h"
#include "health.h"
#include "tank_snd.h"

class Tank : public QObject, public QGraphicsRectItem {
    Q_OBJECT
   public:
    Tank(int x = 0, int y = 0, double ang = 0);
    ~Tank();
    void set_dest(QPointF des, bool reset_gun, bool play_sound);
    void set_target(QPointF tar);
    void set_target(Tank *tar);
    void stop_tracing();
    void set_selected(bool);

    bool selected = false;
    QPointF dest;
    QPointF target;
    Tank *tar_tank = nullptr;
    Base *base;
    Gun *gun;
    Health *health;

    TankSound *tk_snd;
};
