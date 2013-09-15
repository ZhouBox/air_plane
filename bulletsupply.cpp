#include "bulletsupply.h"

BulletSupply::BulletSupply(uint speed, QGraphicsScene *scene,
                           const QPixmaps &pixmaps, int flag, QGraphicsItem *parent):
    Flyer(speed,scene,parent),
    m_pixmap(pixmaps),
    m_flag(flag),
    m_info("")
{
    if (m_flag == BULLETSUPPLYA) {
        m_info = "A";
    } else {
        m_info = "B";
    }
}

QRectF BulletSupply::boundingRect() const
{
    //return QRectF(0,0,40,40);
    return QRectF(m_pixmap.at(m_flag - BULLETSUPPLYA).rect());
}

void BulletSupply::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    //    painter->drawText(0,0,40,40,Qt::AlignCenter,
    //                      tr("%1").arg(m_info));
    painter->drawPixmap(0,0,m_pixmap.at(m_flag - BULLETSUPPLYA));
}

void BulletSupply::autofly()
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
