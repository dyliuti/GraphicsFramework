#include "view.h"
#include "scene.h"
#include "state/statebase.h"
#include <QMouseEvent>

BOARD_NAMESPACE_USE
View::View(QWidget* parent)
    : QGraphicsView(parent)
{
}

void View::mousePressEvent(QMouseEvent* event)
{
    auto scene = getScene();
    const auto& stateMachine = scene->getStateMachine();
    auto scenePos = mapToScene(event->pos());
    auto commonData = stateMachine->getCommonData();
    commonData->pressStartPos = scenePos;
    commonData->scene = scene;

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
