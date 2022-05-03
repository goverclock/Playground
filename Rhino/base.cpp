#include "base.h"

#include <qmath.h>

#include <QGraphicsScene>
#include <QLineF>
#include <QTimer>

#include "health.h"
#include "tank.h"

Base::Base(Tank *par, int x, int y, double angle)
    : QObject(), QGraphicsRectItem() {
    parent = par;

    setRect(0, 0, base_width, base_higth);
    setPos(x, y);
    setTransformOriginPoint(rect().center());

    setRotation(angle);

    QTimer *rotate_timer = new QTimer(this);
    connect(rotate_timer, SIGNAL(timeout()), this, SLOT(rotate_to_dest()));
    rotate_timer->start(10);

    QTimer *forward_timer = new QTimer(this);
    connect(forward_timer, SIGNAL(timeout()), this, SLOT(forward_to_dest()));
    forward_timer->start(10);
}

void Base::rotate_to_dest() {
    if (!rotating) return;

    forward = false;

    QLineF ln(mapToScene(rect().center()), parent->dest);

    int cur = rotation(), des = 360 - ln.angle();
    cur = (cur + 720) % 360;

    int f = 0;
    if (des > cur)
        f = (des - cur < 180) ? 1 : -1;
    else if (des < cur)
        f = (cur - des < 180) ? -1 : 1;

    if (abs(cur - des) >= rotate_rate * 2)
        setRotation(rotation() + f * rotate_rate);
    else {
        setRotation(des);
        rotating = false;
        forward = true;
    }
}

void Base::forward_to_dest() {
    forward_to_target();
    if (!forward) return;

    QLineF ln(mapToScene(rect().center()), parent->dest);

    if (ln.length() < 10) {
        forward = false;
        return;
    }

    double theta = rotation();
    theta = qDegreesToRadians(theta);
    double dx = forward_rate * qCos(theta);
    double dy = forward_rate * qSin(theta);
    setPos(x() + dx, y() + dy);
}

// called in forward_to_dest()
void Base::forward_to_target() {
    if (!tracing) return;
    if (!parent->tar_tank) return;

    auto p = mapRectToScene(rect()).center();
    auto tp =
        parent->tar_tank->base->mapRectToScene(parent->tar_tank->base->rect())
            .center();
    QLineF ln(p, tp);
    double theta = qDegreesToRadians(-ln.angle());
    double dx = (parent->gun->range - 20) * qCos(theta);
    double dy = (parent->gun->range - 20) * qSin(theta);
    QPointF d(tp.x() - dx, tp.y() - dy);

    parent->dest = d;
    rotating = true;
}
