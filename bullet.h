#pragma once
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPointF>
#include <QTimer>
#include "tank.h"
#include "game.h"

class Bullet : public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
   public:
    Bullet(QPointF from, QPointF to, Game *game, Tank *sh);
    Game *parent;
    Tank *shooter;
    int damage;
    int speed;
    int size;
    double angle;
    QPointF dest;
    QTimer *move_timer;

    void explode();
    
   public slots:
    void move();
};
