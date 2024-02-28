#include "scene.h"
#include "state/normalstate.h"
#include "state/penstate.h"
#include "state/selectstate.h"
#include "state/statemachine.h"
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QMimeData>
#include "state/shapestate.h"

const QString MimeType = "application/com.blikoontech.painterapp";

BOARD_NAMESPACE_USE
Scene::Scene(QObject* parent)
    : QGraphicsScene(parent)
    , penColor(Qt::black)
    , penWidth(2)
    , penStyle(Qt::SolidLine)
    , fillColor(Qt::gray)
    , brushStyle(Qt::SolidPattern)
{
    initStateMachine();

    horGuideLine = addLine(-s_guideLineWidth / 2, 0, s_guideLineWidth / 2, 0, QPen(Qt::blue));
    verGuideLine = addLine(0, -s_guideLineWidth / 2, 0, s_guideLineWidth / 2, QPen(Qt::blue));
    setSceneRect(-s_sceneWidth / 2, -s_sceneHeight / 2, s_sceneWidth, s_sceneHeight);

    undoStack = new QUndoStack(this);
}

void Scene::initStateMachine()
{
    m_stateMachine = std::make_unique<StateMachine>(this);
    m_stateMachine->registState(StateType::Normal, std::make_shared<NormalState>());
    m_stateMachine->registState(StateType::Pen, std::make_shared<PenState>());
    m_stateMachine->registState(StateType::Select, std::make_shared<SelectState>());
    m_stateMachine->registState(StateType::BoxSelect, std::make_shared<BoxSelectState>());
    m_stateMachine->registState(StateType::Eraser, std::make_shared<StateBase>());
    m_stateMachine->registState(StateType::Rect, std::make_shared<RectangleState>());
    m_stateMachine->registState(StateType::Cirle, std::make_shared<CircleState>());
    m_stateMachine->registState(StateType::Star, std::make_shared<StateBase>());

    m_stateMachine->switchState(StateType::Normal);
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->property("Key").canConvert(QMetaType::Int)) {
        event->acceptProposedAction();
    } else {
        QGraphicsScene::dragMoveEvent(event);
    }
}

void Scene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->property("Key").canConvert(QMetaType::Int)) {
        int key = event->mimeData()->property("Key").toInt();
        QPen mPen;
        mPen.setColor(penColor);
        mPen.setWidth(penWidth);
        mPen.setStyle(penStyle);

        QBrush mBrush;
        mBrush.setColor(fillColor);
        mBrush.setStyle(brushStyle);

        //        switch (key) {
        //        case 10:{
        //            //Ellipse
        //            ResizableEllipseItem * ellipse = new ResizableEllipseItem();
        //            ellipse->setRect(0,0,80,50);
        //            ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        //            ellipse->setBrush(mBrush);
        //            ellipse->setPen(mPen);

        //            AddCommand* addCommand = new AddCommand(ellipse,this);
        //            undoStack->push(addCommand);
        //            //addItem(ellipse);

        //            ellipse->setPos(event->scenePos() -QPointF((ellipse->boundingRect().width()/2),
        //                                                       (ellipse->boundingRect().height()/2))) ;

        //        }
        //            break;
        //        case 20:{
        //            //Qt Quick Image
        //            ResizablePixmapItem * pixItem = new ResizablePixmapItem(QPixmap(":/images/quick.png"));
        //            pixItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        //            pixItem->setPen(mPen);

        //            //addItem(pixItem);
        //            AddCommand* addCommand = new AddCommand(pixItem,this);
        //            undoStack->push(addCommand);

        //            pixItem->setPos(event->scenePos() -QPointF((pixItem->boundingRect().width()/2),
        //                                                       (pixItem->boundingRect().height()/2))) ;
        //        }
        //            break;
        //        case 30:{
        //            //Rectangle
        //            ResizableRectItem * rectItem = new ResizableRectItem();
        //            rectItem->setRect(0,0,80,50);
        //            rectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        //            rectItem->setBrush(mBrush);
        //            rectItem->setPen(mPen);

        //            //addItem(rectItem);
        //            AddCommand* addCommand = new AddCommand(rectItem,this);
        //            undoStack->push(addCommand);

        //            rectItem->setPos(event->scenePos() -QPointF((rectItem->boundingRect().width()/2),
        //                                                        (rectItem->boundingRect().height()/2))) ;
        //        }
        //            break;
        //        case 40:{
        //            //Star
        //            ResizableStarItem * starItem = new ResizableStarItem();
        //            starItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        //            starItem->setBrush(mBrush);
        //            starItem->setPen(mPen);

        //            // addItem(starItem);
        //            AddCommand* addCommand = new AddCommand(starItem,this);
        //            undoStack->push(addCommand);

        //            starItem->setPos(event->scenePos() -QPointF((starItem->boundingRect().width()/2),
        //                                                        (starItem->boundingRect().height()/2))) ;
        //        }
        //            break;

        //        }
        event->acceptProposedAction();
    } else {
        QGraphicsScene::dropEvent(event);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_stateMachine->mousePressEvent(event);
    }

    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton)) {
        m_stateMachine->mouseMoveEvent(event);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->button() == Qt::LeftButton)) {
        m_stateMachine->mouseReleaseEvent(event);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event)
{
//    if (event->key() == Qt::Key_Delete) {
//        //        if(selectedItems().count()  > 0){
//        //            QGraphicsItem * itemToRemove = selectedItems()[0];
//        //            RemoveCommand * removeCommand = new RemoveCommand(itemToRemove,this);
//        //            undoStack->push(removeCommand);
//        //            //            removeItem(itemToRemove);
//        //            //            delete itemToRemove;
//        //        }
//    }

    QGraphicsScene::keyPressEvent(event);
}


Qt::BrushStyle Scene::getBrushStyle() const
{
    return brushStyle;
}

void Scene::setBrushStyle(const Qt::BrushStyle& value)
{
    brushStyle = value;
}

void Scene::copy()
{
    QByteArray mByteArray;
    QDataStream out(&mByteArray, QIODevice::WriteOnly);
//    writeItemsToDataStream(out, selectedItems());
    QMimeData* mimeData = new QMimeData;
    mimeData->setData(MimeType, mByteArray);
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);
}

void Scene::cut()
{
    QByteArray mByteArray;
    QDataStream out(&mByteArray, QIODevice::WriteOnly);

    QList<QGraphicsItem*> itemList = selectedItems();

//    writeItemsToDataStream(out, itemList);
    QMimeData* mimeData = new QMimeData;
    mimeData->setData(MimeType, mByteArray);
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);

    // Remove items
    foreach (QGraphicsItem* item, itemList) {
        removeItem(item);
    }
    qDeleteAll(itemList);
}

void Scene::paste()
{
    QClipboard* clipboard = QApplication::clipboard();
    const QMimeData* mimeData = clipboard->mimeData();

    if (!mimeData)
        return;

    if (mimeData->hasFormat(MimeType)) {
        QByteArray mByteArray = mimeData->data(MimeType);
        QDataStream in(&mByteArray, QIODevice::ReadOnly);

//        readItemsFromDataStream(in);
    }
}

void Scene::saveScene(QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly))
        return;

    QDataStream dataStream(&file);
//    writeItemsToDataStream(dataStream, items());

    file.close();
}

void Scene::loadScene(QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QDataStream dataStream(&file);
//    readItemsFromDataStream(dataStream, false);
    file.close();
}

void Scene::undo()
{
    undoStack->undo();
}

void Scene::redo()
{
    undoStack->redo();
}

QColor Scene::getFillColor() const
{
    return fillColor;
}

void Scene::setFillColor(const QColor& value)
{
    fillColor = value;
}

Qt::PenStyle Scene::getPenStyle() const
{
    return penStyle;
}

void Scene::setPenStyle(const Qt::PenStyle& value)
{
    penStyle = value;
}

int Scene::getPenWidth() const
{
    return penWidth;
}

void Scene::setPenWidth(int value)
{
    penWidth = value;
}

QColor Scene::getPenColor() const
{
    return penColor;
}

void Scene::setPenColor(const QColor& value)
{
    penColor = value;
}

void Scene::addImageItem(const QString& path)
{
    //    ResizablePixmapItem * pixItem = new ResizablePixmapItem(QPixmap(path));
    //    pixItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    //    addItem(pixItem);

    //    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
    //                                           pixItem->boundingRect().height()/2));
}
