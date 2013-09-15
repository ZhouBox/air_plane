#include "bloodsupply.h"

BloodSupply::BloodSupply(uint speed, QGraphicsScene *scene, QGraphicsItem *parent):
    Flyer(speed, scene, parent),
    m_pic(QPixmap(":/image/blood.png"))
{
}

BloodSupply::~BloodSupply()
{

}


QRectF BloodSupply::boundingRect() const
{
    return m_pic.rect();

}

void BloodSupply::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawPixmap(0,0,m_pic);
}



void BloodSupply::autofly()
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

void BloodSupply::advance(int)
{
    if (!checkPos(Behind)) {
        posLost();
        return;
    }

    QPointF t = scenePos();
    t.ry() += m_speed;
    setPos(t);
}

int BloodSupply::name() const
{
    return GlobalParameter::instance()->bloodSupplyClassFlag;
}
