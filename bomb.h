#ifndef BOMB_H
#define BOMB_H

#include "flyer.h"

#include <QPainter>

class Bomb : public Flyer
{
public:
    Bomb(uint speed, QGraphicsScene *scene, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void autofly();

    virtual void doCollide() {

    }

    virtual int name() const {
        return GlobalParameter::instance()->bombClassFlag;
    }

    virtual void fall() {
        setVisible(false);
        deleteLater();
    }
private:
    QPixmap m_pixmap;
};

#endif // BOMB_H
