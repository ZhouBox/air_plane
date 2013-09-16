#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>
#include "customitem.h"

/**
 * @brief The TextItem class 简单的显示文本信息的项
 */

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit TextItem(const QString &text, QGraphicsItem *parent = 0);
    
    /**
     * @brief type 是为了与飞行系统的项区别
     * @return
     */
    int type() const {
        return CustomItem::Type;
    }
signals:
    
public slots:
    
};

#endif // TEXTITEM_H
