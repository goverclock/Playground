#include "tank.h"

#include <qmath.h>

#include "game.h"

extern Game *game;

Tank::Tank(int x, int y, double ang) : QObject(), QGraphicsRectItem() {
    base = new Base(this, x, y, ang);
    base->setParentItem(this);

    gun = new Gun(this);
    gun->setParentItem(base);

    health = new Health(this);
    health->setParentItem(this);

    tk_snd = new TankSound();
}

Tank::~Tank() {
    tk_snd->play_commander(1);
    delete health;
    delete base;  // base deletes gun
    game->tanks.removeOne(this);
    game->selected_tanks.removeOne(this);
    game->scene->removeItem(this);
    for (auto tk : game->tanks)
        if (tk->tar_tank == this) {
            tk->tar_tank = nullptr;
            tk->gun->locked = false;
        }
}

void Tank::set_dest(QPointF des, bool reset_gun, bool play_sound) {
    if (play_sound) tk_snd->play_move();
    dest = des;
    base->rotating = true;
    base->tracing = false;

    // if out of range, stop targeting, reset gun
    if (tar_tank) {
        auto a = base->mapRectToScene(base->rect()).center();
        auto b =
            tar_tank->base->mapRectToScene(tar_tank->base->rect()).center();
        QLineF ln(a, b);
        if (ln.length() > gun->range + 100) stop_tracing();
    }

    // if already targeting at *ground*, stop it
    if (reset_gun && !tar_tank) gun->locked = false;
}

void Tank::set_target(QPointF tar) {
    // play sound
    tk_snd->play_attack();
    // targeting ground
    tar_tank = nullptr;
    target = mapToScene(tar);
    gun->locked = true;

    auto p = base->mapRectToScene(base->rect()).center();
    QLineF ln(p, tar);
    double theta = qDegreesToRadians(-ln.angle());
    double dx = gun->range * qCos(theta) - 20;
    double dy = gun->range * qSin(theta) - 20;
    tar = QPointF(tar.x() - dx, tar.y() - dy);

    set_dest(tar, false, false);
}

void Tank::set_target(Tank *tar) {
    // play sound
    tk_snd->play_attack();
    // targeting a tank
    tar_tank = tar;
    gun->locked = true;
    base->tracing = true;
}

void Tank::stop_tracing() {
    tar_tank = nullptr;
    gun->locked = false;
}

void Tank::set_selected(bool x) {
    if (x && !selected) tk_snd->play_select();
    selected = x;
}
