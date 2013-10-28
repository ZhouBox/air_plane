#include "enemyplane.h"


#ifdef OBJ_CACHE
QList<void*>* EnemyPlane::m_obj_buffer = new QList<void*>();
#else
QList<void*>* EnemyPlane::m_obj_buffer = NULL;
#endif

EnemyPlane::EnemyPlane(const QList<QPixmap> &animation,
                       uint bloods, uint speed,
                       QGraphicsScene *scene, QGraphicsItem *parent):
    FlightVehicle(animation, bloods, speed, scene, parent)
{
    //connect(this, SIGNAL(visibleChanged()), this, SLOT(slt_cache()));
    if (bloods == LITTLEBLOODS) {
        m_style = LITTLE;
    } else {
        if (bloods == MIDDLEBLOODS) {
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


void EnemyPlane::falling(int step)
{
    if (step < m_steps) {
        setFrame(step);
    } else {
        p_timerLine->stop();
        setVisible(false);
        if (m_style == LITTLE) {
            emit sig_addScore(LITTLE_SCORE);
        } else {
            if (m_style == MIDDLE) {
                emit sig_addScore(MIDDLE_SCORE);
            } else{
                emit sig_addScore(LARGER_SCORE);
            }
        }
        deleteLater();
    }
}


void* EnemyPlane::operator new(size_t size)
{
#ifdef OBJ_CACHE
    void *re = 0;
    if (m_obj_buffer->empty()) {
        re = static_cast<void*>(new char[size]);
        m_obj_buffer->append(re);
    } else {
        re = m_obj_buffer->front();
        m_obj_buffer->pop_front();
    }
    return re;
#else
    return ::operator new(size);
#endif

}

void EnemyPlane::operator delete(void *p)
{
#ifdef OBJ_CACHE
    m_obj_buffer->append(p);
#else
    ::operator delete(p);
#endif
}

void EnemyPlane::clear_all()
{
#ifdef OBJ_CACHE
    qDeleteAll(*m_obj_buffer);
    delete m_obj_buffer;
#else
#endif
}

