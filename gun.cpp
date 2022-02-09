#include "gun.h"

#include <QLineF>
#include <QTimer>

#include "bullet.h"
#include "game.h"
#include "tank.h"

extern Game *game;

Gun::Gun(Tank *par) : QObject(), QGraphicsRectItem() {
    parent = par;

    gun_higth = parent->base->base_width / 7;
    gun_width = parent->base->base_higth;
    fire_load = fire_gap;
    rotate_rate = parent->base->rotate_rate;

    setRect(0, 0, gun_width, gun_higth);
    auto p_b = parent->base;
    QPointF pos(p_b->rect().center().x() - gun_higth / 2,
                p_b->rect().center().y() - gun_higth / 2);
    setPos(pos);
    setTransformOriginPoint(gun_higth / 2, gun_higth / 2);

    QTimer *rotate_timer = new QTimer(this);
    connect(rotate_timer, SIGNAL(timeout()), this,
            SLOT(rotate_lock_to_target()));
    rotate_timer->start(7);

    QTimer *fire_timer = new QTimer(this);
    connect(fire_timer, SIGNAL(timeout()), this, SLOT(load()));
    fire_timer->start(10);
}

void Gun::rotate_lock_to_target() {
    auto tar_tank = parent->tar_tank;
    if (!locked) {
        rotate_lock_reset();
        return;
    }

    QLineF ln;
    if (tar_tank) {  // targeting a tank
        auto a = parent->base->mapRectToScene(parent->base->rect());
        auto b = tar_tank->base->mapRectToScene(tar_tank->base->rect());
        ln = QLineF(a.center(), b.center());
    } else  // targeting the ground
        ln = QLineF(mapToScene(parent->base->rect().center()), parent->target);

    int cur = rotation() + parent->base->rotation(), des = 360 - ln.angle();
    cur = (cur + 720) % 360;

    int f = 0;
    if (des > cur)
        f = (des - cur < 180) ? 1 : -1;
    else if (des < cur)
        f = (cur - des < 180) ? -1 : 1;

    int d = abs(cur - des);
    if (d <= rotate_rate * 5)
        steady = true;  // only when gun is steady, it can fire
    else
        steady = false;

    if (d >= rotate_rate * 2)
        setRotation(rotation() + f * rotate_rate);
    else {
        des = cur;
        setRotation(des - parent->base->rotation());
    }
}

// called from rotate_lock_to_target
void Gun::rotate_lock_reset() {
    int cur = rotation() + parent->base->rotation(),
        des = parent->base->rotation();
    cur = (cur + 720) % 360;

    int f = 0;
    if (des > cur)
        f = (des - cur < 180) ? 1 : -1;
    else if (des < cur)
        f = (cur - des < 180) ? -1 : 1;

    if (abs(cur - des) >= rotate_rate * 2)
        setRotation(rotation() + f * rotate_rate);
    else
        setRotation(des - parent->base->rotation());
}

void Gun::fire() {
    if (!locked || !steady) return;

    bool good = false;
    // fire at tar_tank
    if (parent->tar_tank) {
        // in range?
        auto a = parent->base->mapRectToScene(parent->base->rect()).center();
        auto b = parent->tar_tank->base
                     ->mapRectToScene(parent->tar_tank->base->rect())
                     .center();
        QLineF ln(a, b);
        if (ln.length() <= range) {
            Bullet *bullet = new Bullet(a, b, game, parent);
            game->scene->addItem(bullet);
            good = true;
        }
    } else {  // fire at ground
        auto a = parent->base->mapRectToScene(parent->base->rect()).center();
        QLineF ln(a, parent->target);
        if (ln.length() <= range) {
            auto a =
                parent->base->mapRectToScene(parent->base->rect()).center();
            QLineF ln(a, parent->target);
            if (ln.length() <= range) {
                Bullet *bullet = new Bullet(a, parent->target, game, parent);
                game->scene->addItem(bullet);
                good = true;
            }
        }
    }

    if (good) fire_load = 0;  // successfully fired
}

void Gun::load() {
    if (fire_load < fire_gap) fire_load++;
    if (fire_load >= fire_gap) fire();  // fire resets fire_load if success
}
