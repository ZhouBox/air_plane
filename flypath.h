#ifndef FLYPATH_H
#define FLYPATH_H


#include <vector>


/**
 * @brief The FlyPath class 飞行轨迹,f(x,y)函数
 */
class FlyPath
{
public:
    FlyPath() {}
    virtual ~FlyPath() = 0;
private:
};

FlayPath::~FlyPath()
{

}



/**
 * @brief The BulletFlyPath class 子弹飞行的轨迹,实例，可以在autofly中直接编写控制轨迹代码，也可以继承FlayPath实现轨迹逻辑，供使用
 */

class BulletFlyPath : public FlyPath
{
public:
    BulletFlyPath(double y):m_y(y) {}
    virtual ~BulletFlyPath(){}
    virtual double operator()(double x);
private:
    double m_y;
};

double BulletFlyPath::operator ()(double /*x*/)
{
    return m_y;
}


#endif // FLYPATH_H
