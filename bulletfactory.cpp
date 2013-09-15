#include "bulletfactory.h"

BulletFactory::BulletFactory()
{
}

BulletFactory::Bullets BulletFactory::creator(BULLETFLAG flag, QGraphicsScene *scene)
{
    Bullets re;
    switch (flag) {
    case _1:
        re.append(new Bullet(GlobalParameter::instance()->_1bulletOutline,
                             QColor(123,123,123) ,90,
                             GlobalParameter::instance()->bulletSpeed ,scene));
        break;
    case _2:
        re.append(new Bullet(GlobalParameter::instance()->_1bulletOutline,
                             QColor(123,123,123) ,90,
                             GlobalParameter::instance()->bulletSpeed ,scene));
        re.append(new Bullet(GlobalParameter::instance()->_1bulletOutline,
                             QColor(123,123,123) ,90,
                             GlobalParameter::instance()->bulletSpeed ,scene));
        break;
    case _3:
        for (int i = 0;i < 3;++i) {
            re.append(new Bullet(GlobalParameter::instance()->_1bulletOutline,
                                 QColor(123,123,123) ,80 + 10 * i,
                                 GlobalParameter::instance()->bulletSpeed ,scene));
        }
        break;
    default:
        break;
    }
    return re;
}
