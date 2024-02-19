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
    commonData->pressPos = scenePos;
    //    commonData->scene = scene;
    if (scene && m_toolType == ToolType::Select) {
        auto item = scene->itemAt(scenePos, transform());
        auto state = stateMachine->switchState(StateType::BoxSelect);
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
