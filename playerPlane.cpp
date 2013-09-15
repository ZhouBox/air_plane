#include "playerPlane.h"


PlayerPlane::PlayerPlane(const QList<QPixmap> &animation, uint bloods, uint speed,
                         QGraphicsScene *scene,QGraphicsItem *parent):
    FlightVehicle(animation, bloods, speed, scene, parent),
    m_bulletFlag(BulletFactory::_1),
    m_second(0){

    setPos((scene->width() - PIXMAPWEIGHT)/2, scene->height() - PIXMAPHEIGHT);
    setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);

    connect(&m_bulletDelayTimer, SIGNAL(timeout()), this, SLOT(slt_resetBulletFlag()));
}


QRectF PlayerPlane::boundingRect() const
{
    return m_frames.at(m_currentFrame).boundingRect;
}

void PlayerPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawPixmap(0, 0, m_frames.at(m_currentFrame).pixmap);
}


void PlayerPlane::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W://向上移动
        moveFront();
        event->accept();
        break;
    case Qt::Key_S://向下移动
        moveBehind();
        event->accept();
        break;
    case Qt::Key_A://向左移动
//        leftPosture();
        moveLeft();
        event->accept();
        break;
    case Qt::Key_D://向右移动
//        rightPosture();
        moveRight();
        event->accept();
        break;
        //    case Qt::Key_Space:
        //        shoot();
        //        event->accept();
        //        break;
    default:
        Flyer::keyPressEvent(event);
        break;
    }
}

//void PlayerPlane::keyReleaseEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_A://向左
//    case Qt::Key_D://向右
//        normalPosture();
//        event->accept();
//        break;
//    default:
//        Flyer::keyReleaseEvent(event);
//        break;
//    }
//}


void PlayerPlane::moveFront()
{
    if (checkPos(Front)) {
        QPointF t = scenePos();
        t.ry() -= m_speed;
        setPos(t);
    }

}

void PlayerPlane::moveBehind()
{
    if (checkPos(Behind)) {
        QPointF t = scenePos();
        t.ry() += m_speed;
        setPos(t);
    }


}

void PlayerPlane::moveLeft()
{
    if (checkPos(Left)) {
        QPointF t = scenePos();
        t.rx() -= m_speed;
        setPos(t);
    }

}

void PlayerPlane::moveRight()
{
    if (checkPos(Right)) {
        QPointF t = scenePos();
        t.rx() += m_speed;
        setPos(t);
    }

}

//inline
//void PlayerPlane::leftPosture()
//{
//    setFrame(1);
//}

//inline
//void PlayerPlane::rightPosture()
//{
//    setFrame(2);
//}

//inline
//void PlayerPlane::normalPosture()
//{
//    setFrame(0);
//}



void PlayerPlane::shoot()
{
    BulletFactory::Bullets bp = BulletFactory::creator(m_bulletFlag, scene());
    QPointF p = scenePos();
    //40/2是让子弹在图片的中间发射

    p.ry() -= 20;
    if (m_bulletFlag == BulletFactory::_1) {
        p.rx() += 46/4 * 2;
        foreach (Bullet* b, bp) {
            b->setPos(p);
        }
    } else {
        if (m_bulletFlag == BulletFactory::_2) {
            p.rx() += 46/4 * 1;
            foreach (Bullet* b, bp) {
                b->setPos(p);
                p.rx() += 46/4 * 2;
            }
        } else {
            p.rx() += 46/4 * 2;
            foreach (Bullet* b, bp) {
                b->setPos(p);
            }
        }
    }

}



/**
 * @brief PlayerPlane::doCollide 很容易崩溃的函数
 * @note 如果有加血的项，继承自基类Flyer，这里转换成FlightVehicle，出错
 * 碰撞检测到两个item时程序崩溃，段错误，内存访问失败
 */
void PlayerPlane::doCollide()
{
    foreach (QGraphicsItem *t, collidingItems()) {
        //FlightVehicle *fv = static_cast<FlightVehicle*>(t);
        if (t->type() == CustomItem::Type) {

        } else {
            Flyer *fv = static_cast<Flyer*>(t);
            //            if (fv->name() == ENEMYPLANE) {
            //                fv->setVisible(false);
            //                strike();
            //                if (destroy()) {
            //                    fall();
            //                }
            //            } else {
            //                if (fv->name() == BLOODSUPPLY) {
            //                    //xx->xxx(xx)
            //                    fv->setVisible(false);
            //                    oneBlood();
            //                }
            //            }
            collides(fv, fv->name());
        }
    }
}

void PlayerPlane::collides(Flyer *fv,int flag)
{
    switch (flag) {
    case ENEMYPLANE:
        fv->fall();
        strike();
        if (destroy()) {
            fall();
        }
        m_bulletFlag = BulletFactory::_1;
        if (m_bulletDelayTimer.isActive()) {
            m_bulletDelayTimer.stop();
            emit sig_bulletTimes(0,0);
            m_second = 0;
        }


        break;
    case BLOODSUPPLY:
        fv->fall();
        oneBlood();
        break;
    case BULLETSUPPLYA:
        timerReduce(BulletFactory::_2);
        m_bulletFlag = BulletFactory::_2;
        fv->fall();
        break;
    case BULLETSUPPLYB:
        timerReduce(BulletFactory::_3);
        m_bulletFlag = BulletFactory::_3;
        fv->fall();
        break;
    case BOMB:
        fv->fall();
        emit sig_aBomb();
        break;
    default:
        break;
    }
}

void PlayerPlane::timerReduce(BulletFactory::BULLETFLAG flag)
{
    //QTimer::singleShot(30*1000, this, SLOT(slt_resetBulletFlag()));
    if (flag != m_bulletFlag) {
        m_second = 30;
    } else {
        m_second += 30;
    }
    emit sig_bulletTimes(flag, m_second);
    if (!m_bulletDelayTimer.isActive()) {
        m_bulletDelayTimer.start(1000);
    }

}


void PlayerPlane::slt_resetBulletFlag()
{
    --m_second;
    emit sig_bulletTimes(m_bulletFlag, m_second);
    if (m_second == 0) {
        m_bulletDelayTimer.stop();
        m_bulletFlag = BulletFactory::_1;
    }

}








