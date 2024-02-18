#ifndef MYITEM_H
#define MYITEM_H

#include <QQuickItem>
#include <QQuickPaintedItem>

class MyItem : public QQuickItem // QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MyItem)

public:
    explicit MyItem(QQuickItem *parent = nullptr);
    ~MyItem() override;
};

#endif // MYITEM_H
