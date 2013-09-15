#ifndef BULLET_H
#define BULLET_H

#include "enemyplane.h"
#include "customitem.h"

#include <math.h>
#include <QPainter>



//度数转化为弧度，除以ROTATE
#define ROTATE 57.26



/**
 * @brief The Bullet class 子弹
 */

class Bullet : public Flyer
{
public:
    Bullet(const QPainterPath &path, const QColor &color, qreal angle,
           uint speed, QGraphicsScene *scene, QGraphicsItem *parent = 0);
    virtual ~Bullet(){}

    /**
     * @brief clone 供以后优化使用，不过现体系还不支持
     * @return
     */
    Bullet* clone() const;

    virtual void autofly();

    virtual void advance(int);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void doCollide();

    virtual int name() const;

private:
    /**
     * @brief m_path 用来绘制子弹的形状
     */
    QPainterPath m_path;
    QColor m_color;
    qreal m_angle;
    qreal xSpeed;
    qreal ySpeed;

};

#endif // BULLET_H
