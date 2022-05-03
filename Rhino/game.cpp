#include "game.h"

#include <QGraphicsRectItem>
#include <QLineF>
#include <algorithm>
#include <cstdlib>

Game::Game() : QGraphicsView() {
    // initialize the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, game_width, game_higth);
    setScene(scene);
    setFixedSize(game_width, game_higth);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // initialize frame_timer
    frame_timer = new QTimer();
    frame_timer->start(10);

    // create a tank
    tank = new Tank(400, 200, 45);
    scene->addItem(tank);
    tanks.push_back(tank);

    // create a test tank
    tank0 = new Tank(100, 100, 0);
    scene->addItem(tank0);
    tanks.push_back(tank0);

    QWidget::setMouseTracking(true);
}

void Game::mousePressEvent(QMouseEvent *event) {
    // do nothing but record
    if (event->button() == Qt::LeftButton) {
        mouse_status.left_down = true;
        mouse_status.left_down_pos = event->pos();
    }
    if (event->button() == Qt::RightButton) {
        mouse_status.right_down = true;
        mouse_status.right_down_pos = event->pos();
    }
}

void Game::mouseReleaseEvent(QMouseEvent *event) {
    // released left
    if (event->button() == Qt::LeftButton) {
        mouse_status.left_down = false;
        // is left clicling?
        QLineF ln(mouse_status.left_down_pos, event->pos());
        if (ln.length() < 10) {
            // is clicking on a tank?
            bool clicked_on_tank = false;
            if (key_status.ctl_down) {
                // target the tank
                for (auto tk : tanks) {
                    auto bs = tk->base;
                    if (bs->mapRectToScene(bs->rect()).contains(event->pos())) {
                        clicked_on_tank = true;
                        for (auto stk : selected_tanks)
                            if (stk != tk) {
                                stk->set_target(tk);
                                // qDebug("Targeting a tank");
                            }
                        break;
                    }
                }
                // TODO
                // qDebug("Targeting a tank");
            } else {
                // select the tank
                for (auto tk : tanks) {
                    auto bs = tk->base;
                    if (bs->mapRectToScene(bs->rect()).contains(event->pos())) {
                        clicked_on_tank = true;
                        for (auto stk : selected_tanks)
                            if (stk != tk) stk->set_selected(false);
                        selected_tanks.clear();
                        selected_tanks.push_back(tk);
                        tk->set_selected(true);
                        // qDebug("Selected single");
                        break;
                    }
                }
            }
            // left clicked on ground(set dest)
            if (!clicked_on_tank)
                for (auto tk : selected_tanks) {
                    if (key_status.ctl_down) {
                        tk->set_target(event->pos());
                        // qDebug("Targeting the ground");
                    } else {
                        tk->set_dest(event->pos(), true, true);
                        // qDebug("Set dest");
                    }
                }
        } else {
            // drag
            for (auto stk : selected_tanks) stk->set_selected(false);
            selected_tanks.clear();

            for (auto tk : tanks) {
                auto m_r = mouse_status.select_rect->mapRectToScene(
                    mouse_status.select_rect->rect());
                auto t_r = tk->base->mapRectToScene(tk->base->rect());
                if (t_r.intersects(m_r)) {
                    selected_tanks.push_back(tk);
                    tk->set_selected(true);
                    // qDebug("ONE");
                }
            }

            // qDebug("Drag select");
        }
    }

    // released right
    if (event->button() == Qt::RightButton) {
        mouse_status.right_down = false;
        // is right clicking?
        QLineF ln(mouse_status.right_down_pos, event->pos());
        if (ln.length() < 10) {
            for (auto stk : selected_tanks) stk->selected = false;
            selected_tanks.clear();
            // qDebug("Deselected all");
        }
    }

    // delete select_rect
    if (mouse_status.select_rect != nullptr) {
        scene->removeItem(mouse_status.select_rect);
        delete mouse_status.select_rect;
        mouse_status.select_rect = nullptr;
    }
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    if (!mouse_status.left_down) return;

    if (mouse_status.select_rect == nullptr) {
        mouse_status.select_rect = new QGraphicsRectItem(0, 0, 0, 0);
        scene->addItem(mouse_status.select_rect);
    }

    auto r = mouse_status.select_rect;

    double x, y, w, h;
    x = std::min((int)mouse_status.left_down_pos.x(), event->x());
    y = std::min((int)mouse_status.left_down_pos.y(), event->y());
    w = std::max((int)mouse_status.left_down_pos.x(), event->x()) - x;
    h = std::max((int)mouse_status.left_down_pos.y(), event->y()) - y;

    r->setPos(x, y);
    r->setRect(0, 0, w, h);
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Control) key_status.ctl_down = true;

    // test health
    for (auto tk : selected_tanks) {
        if (event->key() == Qt::Key_Minus) tk->health->health_decrease(100);
        if (event->key() == Qt::Key_Equal) tk->health->health_increase(100);
        tk->health->health_reposition();
    }

    if(event->key() == Qt::Key_S) {
        Tank *ntk = new Tank(rand() % game_width, rand() % game_higth, rand() % 360);
        scene->addItem(ntk);
        tanks.push_back(ntk);
        ntk->tk_snd->play_commander(0);
    }
}

void Game::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Control) key_status.ctl_down = false;
}
