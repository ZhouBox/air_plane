#ifndef FRAME_H
#define FRAME_H


#include <QPixmap>
#include <QRectF>

/**
 * @brief The Frame struct 玩家飞机用到的几个图片,不同状态
 */
struct Frame {
    QPixmap pixmap;
    QPainterPath shape;
    QRectF boundingRect;
};

#endif // FRAME_H
