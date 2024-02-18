#include "myitem.h"
#include <QPainter>

MyItem::MyItem(QQuickItem *parent)
    : QQuickItem(parent) //  QQuickPaintedItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    //setFillColor(Qt::blue);
}

MyItem::~MyItem()
{
}

//void MyItem::paintEvent(QPainter *painter)
//{
//    painter->fillRect(boundingRect(), Qt::blue);
//}
