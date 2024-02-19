//
// Created by yanminwei on 2024/2/3.
//
#ifndef BOARD_VIEW_H
#define BOARD_VIEW_H

#include "board_global.h"
#include "boarddefine.h"
#include <QGraphicsView>

BOARD_NAMESPACE_BEGIN
class Scene;
class BOARD_EXPORT View : public QGraphicsView {
public:
    explicit View(QWidget* parent = nullptr);
    void setToolType(ToolType type) { m_toolType = type; }

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Board::Scene* getScene();

private:
    ToolType m_toolType { ToolType::Cursor };
};
BOARD_NAMESPACE_END

#endif // BOARD_VIEW_H
