#include "view.h"
#include "scene.h"
#include "state/statebase.h"
#include "state/statemachine.h"
#include <QDebug>
#include <QMouseEvent>

BOARD_NAMESPACE_USE
View::View(QWidget* parent)
    : QGraphicsView(parent)
{
}

void View::mousePressEvent(QMouseEvent* event)
{
    auto scene = getScene();
    if(!scene) {
        return;
    }
    const auto& stateMachine = scene->getStateMachine();
    if (stateMachine->isCureentSelectType() && event->button() == Qt::LeftButton) {
        auto item = scene->itemAt(mapToScene(event->pos()), transform());
        stateMachine->switchState(item ? StateType::Select : StateType::BoxSelect);
    }

    QGraphicsView::mousePressEvent(event);
}

void View::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

Scene* View::getScene()
{
    return dynamic_cast<Scene*>(scene());
}
