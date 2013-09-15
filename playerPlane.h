#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "flightvehicle.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

#include <QGraphicsSceneMouseEvent>


#include <bulletfactory.h>

#include "customitem.h"





/**
 * @brief The PlayerPlane class 玩家飞机
 */

class PlayerPlane : public FlightVehicle
{
public:
    PlayerPlane(const QList<QPixmap> &animation, uint bloods,
                uint speed, QGraphicsScene *scene,QGraphicsItem *parent = 0);/*:
        FlightVehicle(animation, bloods, speed, scene, parent),
        m_bulletFlag(BulletFactory::_1),
        m_second(0){

        setPos((scene->width() - PIXMAPWEIGHT)/2, scene->height() - PIXMAPHEIGHT);
        setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
    }*/
    ~PlayerPlane(){}
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void autofly() {
        doCollide();
    }


    virtual void advance(int) {
        doCollide();
    }

    virtual void reinit() {
        setPos(scene()->width()/2, scene()->height() - PIXMAPHEIGHT);
        setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
        m_bulletFlag = BulletFactory::_1;
        fullBlood();
    }

    virtual void posLost() {

    }



    /**
     * @brief setBulletFlag 改变当前的子弹模式
     * @param flag
     */
    void setBulletFlag(BulletFactory::BULLETFLAG flag) {
        m_bulletFlag = flag;
    }


    virtual int name() const {
        return GlobalParameter::instance()->playerPlaneClassFlag;
    }


    virtual void doCollide();

public slots:
    /**
     * @brief shoot 射击
     */
    void shoot();



signals:

protected:
    /**
     * @brief keyPressEvent 响应wasd按键
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

//    void keyReleaseEvent(QKeyEvent *event);

protected slots:
    void slt_resetBulletFlag();
    void slt_cache() {

    }

private:
    BulletFactory::BULLETFLAG m_bulletFlag;

    int m_second;

    QTimer m_bulletDelayTimer;




    /**
     * @brief moveFront 向前移动
     */
    void moveFront();
    /**
     * @brief movebehind 向后移动
     */
    void moveBehind();
    /**
     * @brief moveLeft 向左移动
     */
    void moveLeft();
    /**
     * @brief moveRight 向右移动
     */
    void moveRight();
    /**
     * @brief leftPosture 向左移动姿势
     */
   // void leftPosture();
    /**
     * @brief rightPosture 向右移动姿势
     */
   // void rightPosture();


  //  void normalPosture();


    void collides(Flyer *fv, int flag);

    void timerReduce(BulletFactory::BULLETFLAG flag);



};


#endif // PLAYERPLANE_H
