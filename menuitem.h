#ifndef MENUITEM_H
#define MENUITEM_H

#include "customitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class MenuItem : public CustomItem
{
    Q_OBJECT
public:
    explicit MenuItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
signals:
    //点击
    void sig_menu();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    //QPixmap m_menuPix;
    
};

#endif // MENUITEM_H
