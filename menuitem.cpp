#include "menuitem.h"

MenuItem::MenuItem(QGraphicsItem *parent) :
    CustomItem(parent)//,m_menuPix(":/image/menu.png")
{
}

QRectF MenuItem::boundingRect() const
{
    //return m_menuPix.rect();
    return QRectF(0,0,30,30);
}

void MenuItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    //painter->drawPixmap(0,0,m_menuPix);
    painter->drawText(0,0,30,25, Qt::AlignCenter,tr("M"));
}

void MenuItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit sig_menu();
        event->accept();
    }
}
