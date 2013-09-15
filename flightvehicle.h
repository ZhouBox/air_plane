#ifndef FLIGHTVEHICLE_H
#define FLIGHTVEHICLE_H

#include "flyer.h"
#include "frame.h"

/**
 * @brief The FlightVehicle class 飞行器基类，继承自飞行物体类
 */
class FlightVehicle : public Flyer
{
    Q_OBJECT
public:
    FlightVehicle(const QList<QPixmap> &animation, uint bloods, uint speed,
                  QGraphicsScene *scene,QGraphicsItem *parent = 0):Flyer(speed, scene, parent),
        m_currentFrame(0),
        m_bloods(bloods),
        m_blood(bloods){
        for (int i = 0; i < animation.size(); ++i) {
            QPixmap pixmap = animation.at(i);
            Frame frame;
            frame.pixmap = pixmap;
            frame.shape = QPainterPath();
            frame.boundingRect = pixmap.rect();
            m_frames << frame;
        }



    }

    virtual ~FlightVehicle(){}

    virtual void autofly() = 0;
    /**
     * @brief destroy 判断飞行器是否销毁
     * @return
     */

    virtual void advance(int) {

    }

    bool destroy() const;
    /**
     * @brief strike 受到撞击,血减少
     */
    void strike();
    /**
     * @brief fullBlood 满血
     */
    void fullBlood();

    virtual void reinit() {
        fullBlood();
    }


    void oneBlood() {
        if (m_blood < m_bloods) {
            ++m_blood;
            emit sig_blood(m_blood);
        }
    }


    int bloods() const {
        return m_blood;
    }





public slots:
    virtual void shoot() = 0;



signals:
    /**
     * @brief sig_addScore 加分
     */
    void sig_addScore(int score);


    void sig_blood(int blood);

    void sig_bulletTimes(int flag, int sec);

    void sig_aBomb();

protected slots:
    /**
     * @brief slt_resetBulletFlag 不在这里定义，在子类定义，通过槽调用不到？
     * why？
     */
    virtual void slt_resetBulletFlag() = 0;


    virtual void slt_cache() = 0;

protected:


    /**
     * @brief currentFrame 当前的图片
     */

    int m_currentFrame;


    /**
     * @brief m_bloods 初始血量
     */
    uint m_bloods;

    /**
     * @brief m_blood 生命 =0 仆街
     */
    uint m_blood;


    QList<Frame> m_frames;


    void setFrame(int frame) {
        if (!m_frames.isEmpty()) {
            prepareGeometryChange();
            m_currentFrame = frame % m_frames.size();
        }
    }

};

inline
bool FlightVehicle::destroy() const
{
    return m_blood == 0;

}

inline
void FlightVehicle::strike()
{
    --m_blood;
    emit sig_blood(m_blood);
}

inline
void FlightVehicle::fullBlood()
{
    m_blood = m_bloods;
}



#endif // FLIGHTVEHICLE_H
