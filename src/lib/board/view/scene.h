//
// Created by yanminwei on 2024/2/3.
//
#ifndef BOARD_SCENE_H
#define BOARD_SCENE_H

#include "board_global.h"
#include "state/statemachine.h"
#include <QGraphicsScene>
#include <QUndoStack>

BOARD_NAMESPACE_BEGIN
enum class StateType;
class StateMachine;
class BOARD_EXPORT Scene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Scene(QObject* parent = nullptr);
    // stateMachine属于scene但注册状态应该由view层定义
    const std::unique_ptr<StateMachine>& getStateMachine() { return m_stateMachine; }

    void addImageItem(const QString& path);

    QColor getPenColor() const;
    void setPenColor(const QColor& value);

    int getPenWidth() const;
    void setPenWidth(int value);

    Qt::PenStyle getPenStyle() const;
    void setPenStyle(const Qt::PenStyle& value);

    QColor getFillColor() const;
    void setFillColor(const QColor& value);

    Qt::BrushStyle getBrushStyle() const;
    void setBrushStyle(const Qt::BrushStyle& value);

    void copy();
    void cut();
    void paste();

    void saveScene(QString& filename);
    void loadScene(QString& filename);

    void undo();
    void redo();

protected:
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

protected:
    virtual void initStateMachine();

private:
    std::unique_ptr<StateMachine> m_stateMachine;

private:
    QGraphicsLineItem* horGuideLine;
    QGraphicsLineItem* verGuideLine;

    QColor penColor;
    int penWidth;
    Qt::PenStyle penStyle;
    QColor fillColor;
    Qt::BrushStyle brushStyle;
    QUndoStack* undoStack;

    QList<QGraphicsItem*> m_selectedItems;
    QList<QPointF> selectedItemInitialPositions;
};
BOARD_NAMESPACE_END

#endif // BOARD_SCENE_H
