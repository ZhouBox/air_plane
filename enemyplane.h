#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "flightvehicle.h"

#include <QPainter>


//#define OBJ_CACHE


/**
 * @brief The EnemyPlane class 敌机
 */

class EnemyPlane : public FlightVehicle
{
public:
    typedef enum{LITTLE, MIDDLE, LARGER} STYLE;

    EnemyPlane(const QList<QPixmap> &animation, uint bloods,
               uint speed, QGraphicsScene *scene,QGraphicsItem *parent = 0);
    virtual ~EnemyPlane(){}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    virtual void autofly();

    virtual void advance(int);



    virtual void posLost();


    virtual void falling(int step);


    virtual int name() const;


    virtual void doCollide() {

    }

    /**
     * @brief style 那类飞机
     * @return
     */
    STYLE style() const {
        return m_style;
    }


    static void* operator new(size_t size);

    static void operator delete(void *p);


    static QList<void*> *m_obj_buffer;


    static void clear_all();



public slots:
    virtual void shoot() {

    }

protected slots:
    virtual void slt_resetBulletFlag() {

    }

    void slt_cache() {
        // if (!isVisible()) {
        //     GlobalParameter::instance()->p_eplC->push_back(this);
        // }
    }
private:



    STYLE m_style;





};

#endif // ENEMYPLANE_H
