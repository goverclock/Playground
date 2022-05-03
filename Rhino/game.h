#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector>
#include <QTimer>

#include "mouse_status.h"
#include "key_status.h"
#include "tank.h"

class Game : public QGraphicsView {
   public:
    Game();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    const int game_width = 1500;
    const int game_higth = 900;
    QGraphicsScene *scene;
    MouseStatus mouse_status;
    KeyStatus key_status;
    QTimer *frame_timer;
    
    QVector<Tank *> selected_tanks;
    QVector<Tank *> tanks;
    Tank *tank;
    Tank *tank0;
};
