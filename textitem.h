#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>
#include "customitem.h"

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit TextItem(const QString &text, QGraphicsItem *parent = 0);
    

    int type() const {
        return CustomItem::Type;
    }
signals:
    
public slots:
    
};

#endif // TEXTITEM_H
