#ifndef BLOODSUPPLY_H
#define BLOODSUPPLY_H

#include "flyer.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "customitem.h"

/**
 * @brief The BloodSupply class 生命补给
 */


class BloodSupply : public Flyer
{
public:
    BloodSupply(uint speed, QGraphicsScene *scene, QGraphicsItem *parent = 0);
    ~BloodSupply();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void autofly();

    virtual void advance(int);

    virtual void doCollide() {

    }

    virtual int name() const;

    virtual void fall() {
        setVisible(false);
        deleteLater();
    }

private:
    /**
     * @brief m_pic 用的图片资源
     */
    QPixmap m_pic;
};



#endif // BLOODSUPPLY_H
