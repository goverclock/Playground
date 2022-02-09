#pragma once

#include <QPointF>
#include <QGraphicsRectItem>

struct MouseStatus {
    bool left_down = false;
    bool right_down = false;
    QPointF left_down_pos;
    QPointF right_down_pos;
    QGraphicsRectItem *select_rect = nullptr;
};
