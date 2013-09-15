#ifndef BULLETFLYPATH_H
#define BULLETFLYPATH_H

#include "flypath.h"

/**
 * @brief The BulletFlyPath class 子弹飞行的轨迹,实例，可以在autofly中直接编写控制轨迹代码，也可以继承FlayPath实现轨迹逻辑，供使用
 */

class BulletFlyPath : public FlyPath
{
public:
    BulletFlyPath(double y):m_y(y) {}
    virtual ~BulletFlyPath(){}
    double operator()(double x);
private:
    double m_y;
};

double BulletFlyPath::operator ()(double /*x*/)
{
    return m_y;
}



#endif // BULLETFLYPATH_H
