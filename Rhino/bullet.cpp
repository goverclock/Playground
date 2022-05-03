#include "bullet.h"

#include "qmath.h"

Bullet::Bullet(QPointF from, QPointF to, Game *game, Tank *sh)
    : QObject(), QGraphicsEllipseItem() {
    parent = game;
    shooter = sh;
    damage = 100;
    speed = 3;
    size = 20;
    angle = -QLineF(from, to).angle();
    dest = to;
    move_timer = new QTimer();
    move_timer->start(3);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));

    setRect(0, 0, size, size);
    QPointF p(from.x() - size / 2, from.y() - size / 2);
    setPos(p);
}

void Bullet::move() {
    double theta = qDegreesToRadians(angle);
    double dx = speed * qCos(theta);
    double dy = speed * qSin(theta);
    setPos(x() + dx, y() + dy);

    if (QLineF(pos(), dest).length() <= 20) explode();
}

void Bullet::explode() {
    for (auto tk : parent->tanks) {
        if (tk == shooter) continue;
        auto m_a = mapRectToScene(rect());
        auto m_b = tk->base->mapRectToScene(tk->base->rect());
        if (m_a.intersects(m_b)) {
            if (tk->health->cur_health <= damage) {
                // shooter stop targeting the target
                // because the target is deleted and no longer accessiable
                shooter->tar_tank = nullptr;
                shooter->gun->locked = false;
            }
            tk->health->health_decrease(damage);
            break;
        }
    }

    disconnect(move_timer);
    delete move_timer;
    parent->scene->removeItem(this);
    delete this;
}
