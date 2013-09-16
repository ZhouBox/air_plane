#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include <bullet.h>
#include <QGraphicsScene>

/**
 * @brief The BulletFactory class 子弹的工厂类
 */

class BulletFactory
{
public:

    typedef QList<Bullet*> Bullets;

    typedef enum{_1, _2, _3} BULLETFLAG;

    static Bullets creator(BULLETFLAG flag, QGraphicsScene *scene);
private:
    BulletFactory();
};

#endif // BULLETFACTORY_H
