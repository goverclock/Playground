#pragma once
#include <QGraphicsRectItem>
#include <QObject>
#include <QPointF>

class Tank;

class Base : public QObject, public QGraphicsRectItem {
    Q_OBJECT
   public:
    Base(Tank *par, int x = 0, int y = 0, double angle = 0);

    Tank *parent;
    const int base_width = 150;
    const int base_higth = 100;
    double rotate_rate = 3;
    double forward_rate = 3;
    bool rotating = false;
    bool tracing = false;
    bool forward = false;

   public slots:
    void rotate_to_dest();
    void forward_to_dest();
    void forward_to_target();
};
