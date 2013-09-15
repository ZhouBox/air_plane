#ifndef FLYER_H
#define FLYER_H

#include <QGraphicsObject>
#include <QGraphicsScene>

#include <QDebug>

#include "global.h"


/**
 * @brief The Flyer class 飞行物体的基类
 */
class Flyer : public QGraphicsObject
{
    Q_OBJECT
public:
    Flyer(uint speed, QGraphicsScene *scene, QGraphicsItem *parent = 0):QGraphicsObject(parent),
        m_speed(speed){
        scene->addItem(this);
    }
    virtual ~Flyer() {}
    /**
     * @brief fly 对飞行轨迹的描述，自动
     */
    virtual void autofly() = 0;

    /**
     * @brief advance
     * This virtual function is called twice for all items
     * by the QGraphicsScene::advance() slot. In the first phase,
     * all items are called with phase == 0,
     * indicating that items on the scene are about to advance,
     * and then all items are called with phase == 1.
     * Reimplement this function to update your item if you need simple scene-controlled animation.
     */
    virtual void advance(int /*phase*/) {

    }

    /**
     * @brief reinit 重新init
     */
    virtual void reinit() {

    }

    void setSpeed(uint speed);

    /**
     * @brief posLost 当checkpos失败时，物体就要从场景中取出来，缓存起来，重新初始化后再使用
     */
    virtual void posLost() {
        setVisible(false);
        deleteLater();
    }

    /**
     * @brief name 用来标识类，在类转换时使用
     * @return
     */
    virtual int name() const = 0;

    /**
     * @brief doCollide 处理与本item碰撞的项
     * @param list
     */
    virtual void doCollide() = 0;


    /**
     * @brief fall 坠落
     */
    virtual void fall(){
        setFlag(QGraphicsItem::ItemIsMovable, false);
        setFlag(QGraphicsItem::ItemIsFocusable, false);
        emit sig_fall();
    }


signals:
    void sig_fall();


protected:
    typedef enum{Front, Behind, Left, Right} CHECK_FLAG;// w s a d


    /**
     * @brief checkPos 检测位置,返回true在场景中可以移动
     */
    bool checkPos(CHECK_FLAG flag);
    /**
     * @brief m_speed 移动速度
     */
    uint m_speed;
};


inline //加了inline就不报错，why?
void Flyer::setSpeed(uint speed)
{
    m_speed = speed;
}


/**
 * @brief Flyer::checkPos
 * @param flag
 * @return
 * @note 40 ，20 未图片的长和宽
 */
inline
bool Flyer::checkPos(CHECK_FLAG flag)
{
    bool re = false;
    switch (flag) {
    case Front:
        //比较代码
        if (scenePos().ry() > 0) {
            re = true;
        }
        break;
    case Behind:
        if (scenePos().ry() < scene()->height() - PIXMAPHEIGHT) {
            re = true;
        }
        break;
    case Left:
        if (scenePos().rx() > 0) {
            re = true;
        }
        break;
    case Right:
        if (scenePos().rx() < scene()->width() - PIXMAPWEIGHT) {
            re = true;
        }
        break;

    default:
        break;
    }
    return re;
}


#endif // FLYER_H
