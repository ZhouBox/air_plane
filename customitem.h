#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QGraphicsObject>

class CustomItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum {Type = UserType + 1};
    explicit CustomItem(QGraphicsItem *parent = 0);
    int type() const {
        return Type;
    }
    
signals:
    
public slots:
    
};

#endif // CUSTOMITEM_H
