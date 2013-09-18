/********************************************************************
* author 周翔
* e-mail 604487178@qq.com
* blog http://blog.csdn.net/zhx6044
**********************************************************************/

#include "flightvehicle.h"

void FlightVehicle::fall()
{
    m_speed = 0;
    p_timerLine = new QTimeLine(1000/24 * 1.5 * m_steps, this);
    p_timerLine->setUpdateInterval(1000/24 * 1.5);
    p_timerLine->setFrameRange(1, m_steps);
    connect(p_timerLine, SIGNAL(frameChanged(int)), this, SLOT(falling(int)));
    p_timerLine->start();
}

void FlightVehicle::falling(int step)
{
//    logger() << step;
    if (step < m_steps) {
        setFrame(step);
    } else {
        p_timerLine->stop();
        emit sig_fall();
    }

}


