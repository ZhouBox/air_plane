#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QGraphicsObject>


/**
 * @brief The CustomItem class 作为可以显示在界面，不过不是飞行系统的一部分的项的基类
 */

class CustomItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum {Type = UserType + 1};
    explicit CustomItem(QGraphicsItem *parent = 0);

    /**
     * @brief type 是为了与飞行系统的项区别
     * @return
     */
    int type() const {
        return Type;
    }
    
signals:
    
public slots:
    
};

#endif // CUSTOMITEM_H
