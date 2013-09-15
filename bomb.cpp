#include "bomb.h"

Bomb::Bomb(uint speed, QGraphicsScene *scene, QGraphicsItem *parent):
    Flyer(speed, scene, parent)
{
    m_pixmap.load("://image/bomb.png");
}

QRectF Bomb::boundingRect() const
{
    //return QRectF(0,0,40,40);
    return QRectF(m_pixmap.rect());
}

void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    //painter->drawText(0,0,40,40,Qt::AlignCenter,"#");
    painter->drawPixmap(0,0,m_pixmap);

}

void Bomb::autofly()
{
    if (!checkPos(Behind)) {
        posLost();
        return;
    }

    QPointF t = scenePos();
    t.ry() += m_speed;
    setPos(t);

    doCollide();

}

