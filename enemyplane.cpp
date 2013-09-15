#include "enemyplane.h"

EnemyPlane::EnemyPlane(const QList<QPixmap> &animation,
                       uint bloods, uint speed,
                       QGraphicsScene *scene, QGraphicsItem *parent):
    FlightVehicle(animation, bloods, speed, scene, parent)
{
    //connect(this, SIGNAL(visibleChanged()), this, SLOT(slt_cache()));
    if (bloods == 1) {
        m_style = LITTLE;
    } else {
        if (bloods == 7) {
            m_style = MIDDLE;
        } else {
            m_style = LARGER;
        }
    }
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
    if (m_style == LITTLE) {
        emit sig_addScore(1);
    } else {
        if (m_style == MIDDLE) {
            emit sig_addScore(5);
        } else{
            emit sig_addScore(10);
        }
    }

}


