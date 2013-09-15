#include "enemyplane.h"

EnemyPlane::EnemyPlane(const QList<QPixmap> &animation,
                       uint bloods, uint speed,
                       QGraphicsScene *scene, QGraphicsItem *parent):
    FlightVehicle(animation, bloods, speed, scene, parent)
{
    //connect(this, SIGNAL(visibleChanged()), this, SLOT(slt_cache()));
}


QRectF EnemyPlane::boundingRect() const
{
    return m_frames.at(m_currentFrame).boundingRect;

}

void EnemyPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawPixmap(0, 0, m_frames.at(m_currentFrame).pixmap);
}


int EnemyPlane::name() const
{
    return GlobalParameter::instance()->enemyPlaneClassFlag;
}

void EnemyPlane::autofly()
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


void EnemyPlane::advance(int)
{
    if (!checkPos(Behind)) {
        posLost();
        return;
    }

    QPointF t = scenePos();
    t.ry() += m_speed;
    setPos(t);


}

void EnemyPlane::posLost()
{
    setVisible(false);
    deleteLater();
}

void EnemyPlane::fall()
{
    setVisible(false);
    deleteLater();
    emit sig_addScore(1);
}


