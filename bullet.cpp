#include "bullet.h"

Bullet::Bullet(const QPainterPath &path, const QColor &color, qreal angle, uint speed, QGraphicsScene *scene,
               QGraphicsItem *parent):Flyer(speed, scene, parent),
    m_path(path),
    m_color(color),
    m_angle(angle),
    xSpeed(::cos(m_angle / ROTATE) * m_speed),
    ySpeed(::sin(m_angle / ROTATE) * m_speed)
{
}


Bullet* Bullet::clone() const
{
    return NULL;
}

QRectF Bullet::boundingRect() const
{
    return m_path.boundingRect();
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_color);
    painter->drawPath(m_path);
}

/**
 * @brief Bullet::autofly 初定一秒更新一次，那么速度为每秒速度 50ms更新一次
 */

void Bullet::autofly()
{
    if (!checkPos(Front)) {
        posLost();
        return;
    }

    //需要度数转化为弧度
    //    qreal xSpeed = ::cos(m_angle / ROTATE) * m_speed;
    //    qreal ySpeed = ::sin(m_angle / ROTATE) * m_speed;
    QPointF t = scenePos();
    t.rx() -= xSpeed;
    t.ry() -= ySpeed;
    setPos(t);

    doCollide();
}

void Bullet::advance(int)
{
    if (!checkPos(Front)) {
        posLost();
        return;
    }

    //需要度数转化为弧度,提前计算可以可以提高性能
    //    qreal xSpeed = ::cos(m_angle / ROTATE) * m_speed;
    //    qreal ySpeed = ::sin(m_angle / ROTATE) * m_speed;
    QPointF t = scenePos();
    t.rx() -= xSpeed;
    t.ry() -= ySpeed;
    setPos(t);

    doCollide();

}



int Bullet::name() const
{
    return GlobalParameter::instance()->bulletClassFlag;
}


void Bullet::doCollide()
{
    foreach (QGraphicsItem *t, collidingItems()) {
        if (t->type() == CustomItem::Type) {

        } else {
            Flyer *fy = static_cast<Flyer*>(t);
            if (fy->name() == ENEMYPLANE) {
                FlightVehicle* fv = static_cast<FlightVehicle*>(fy);
                this->setVisible(false);
                fv->strike();
                if (fv->destroy()) {
                    fv->fall();
                    //缓存起来
                }

            }

        }

    }
}



