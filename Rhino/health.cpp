#include "health.h"

#include <QTimer>

#include "tank.h"

Health::Health(Tank *par) {
    parent = par;
    double hp_percent = (double)cur_health / (double)max_health;
    auto p_base = parent->base;
    double max_len = p_base->base_higth;

    setRect(0, 0, max_len * hp_percent, 15);
    setPos(p_base->x() + p_base->rect().width() / 2.0 - max_len / 2,
           p_base->y() - p_base->rect().height() / 2);

    QTimer *health_timer = new QTimer();
    connect(health_timer, SIGNAL(timeout()), this, SLOT(health_reposition()));
    health_timer->start(10);

    if (parent->selected)
        setVisible(true);
    else
        setVisible(false);
}

void Health::health_reposition() {
    double hp_percent = (double)cur_health / (double)max_health;
    auto p_base = parent->base;
    double max_len = p_base->base_higth;

    setRect(0, 0, max_len * hp_percent, 15);
    setPos(p_base->x() + p_base->rect().width() / 2.0 - max_len / 2,
           p_base->y() - p_base->rect().height() / 2);

    // visible only when selected
    if (parent->selected)
        setVisible(true);
    else
        setVisible(false);
}

void Health::health_decrease(int x) {
    cur_health -= x;
    if (cur_health <= 0)
        delete parent;
}

void Health::health_increase(int x) { cur_health += x; }
