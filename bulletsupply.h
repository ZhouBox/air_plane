#ifndef BULLETSUPPLY_H
#define BULLETSUPPLY_H

#include "flyer.h"


#include <QPainter>

class BulletSupply : public Flyer
{
public:
    BulletSupply(uint speed, QGraphicsScene *scene, const QPixmaps & pixmaps = QPixmaps(),
                 int flag = BULLETSUPPLYA, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void autofly();

    virtual void advance(int) {

    }


    virtual void doCollide() {

    }

    virtual int name() const {
        return m_flag;
    }

    virtual void fall() {
        setVisible(false);
        deleteLater();
    }

private:
    QPixmaps m_pixmap;

    int m_flag;

    QString m_info;
};

#endif // BULLETSUPPLY_H
