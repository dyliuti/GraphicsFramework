#include "resizablehandlerect.h"
#include <QDebug>
#include <QGraphicsScene>

using namespace Board::Opengl;
ResizableHandleRect::ResizableHandleRect()
{
}

ResizableHandleRect::~ResizableHandleRect()
{
}

void ResizableHandleRect::drawHandles()
{
    // Populate handles in list
    if (m_handleList.count() == 0) {
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::TopLeft));
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::TopRight));
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::BottomRight));
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::BottomLeft));
    }

    // Set up pen
    QPen mPen;
    mPen.setWidth(2);
    mPen.setColor(Qt::black);

    // Top left handle
    QPointF topLeftCorner = rectBounds().topLeft() + QPointF(-12.0, -12.0);
    auto topleftHandleRect = QRectF(topLeftCorner, QSize(12, 12));
    m_handleList[0]->setRect(topleftHandleRect);
    if (!m_handleList.isEmpty()) {
        m_handleList[0]->setPen(mPen);
        m_handleList[0]->setBrush(QBrush(Qt::gray));
        m_ownerItem->scene()->addItem(m_handleList[0].get());
        m_handleList[0]->setParentItem(m_ownerItem);
    }

    // Top right
    QPointF topRightCorner = rectBounds().topRight() + QPointF(0, -12.0);
    auto topRightHandleRect = QRectF(topRightCorner, QSize(12, 12));
    m_handleList[1]->setRect(topRightHandleRect);
    if (!m_handleList.isEmpty()) {
        m_handleList[1]->setPen(mPen);
        m_handleList[1]->setBrush(QBrush(Qt::gray));
        m_ownerItem->scene()->addItem(m_handleList[1].get());
        m_handleList[1]->setParentItem(m_ownerItem);
    }

    // Bottom right
    QPointF bottomRightCorner = rectBounds().bottomRight() + QPointF(0, 0);
    auto bottomRightHandleRect = QRectF(bottomRightCorner, QSize(12, 12));
    m_handleList[2]->setRect(bottomRightHandleRect);
    if (!m_handleList.isEmpty()) {
        m_handleList[2]->setPen(mPen);
        m_handleList[2]->setBrush(QBrush(Qt::gray));
        m_ownerItem->scene()->addItem(m_handleList[2].get());
        m_handleList[2]->setParentItem(m_ownerItem);
    }

    // Bottom left
    QPointF bottomLeftCorner = rectBounds().bottomLeft() + QPointF(-12, 0);
    auto bottomLeftHandleRect = QRectF(bottomLeftCorner, QSize(12, 12));
    m_handleList[3]->setRect(bottomLeftHandleRect);
    if (!m_handleList.isEmpty()) {
        m_handleList[3]->setPen(mPen);
        m_handleList[3]->setBrush(QBrush(Qt::gray));
        m_ownerItem->scene()->addItem(m_handleList[3].get());
        m_handleList[3]->setParentItem(m_ownerItem);
    }
}

void ResizableHandleRect::setOwnerItem(QGraphicsItem* value)
{
    m_ownerItem = value;
}

void ResizableHandleRect::drawHandlesIfNecessary()
{
    if (!m_ownerItem) {
        qWarning() << "ResizableHandleRect : No m_ownerItem set. Not drawing any\
                      handle. Please call setm_ownerItem on your ResizableHandleRect subclass";
        return;
    }

    if (m_ownerItem->isSelected()) {
        drawHandles();
    } else {
        // Remove the handles
        foreach (auto handleItem, m_handleList) {
            m_ownerItem->scene()->removeItem(handleItem.get());
        }
        //        qDeleteAll(m_handleList);  // ToDo: 在item的析构函数中看下有没析构了
        m_handleList.clear();
    }
}
