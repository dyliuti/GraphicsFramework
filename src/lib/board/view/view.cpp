#include "view.h"
#include "scene.h"
#include "state/selectstate.h"
#include "state/statebase.h"
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
    const auto& stateMachine = scene->getStateMachine();
    if (stateMachine->isCureentSelectType() && event->button() == Qt::LeftButton) {
        auto item = scene->itemAt(mapToScene(event->pos()), transform());
        qInfo() << "111111: " << __FUNCTION__ << (item ? (int)StateType::SingleSelect : (int)StateType::BoxSelect);
        stateMachine->switchState(item ? StateType::SingleSelect : StateType::BoxSelect);
        if (item) {
            auto state = std::dynamic_pointer_cast<SingleSelectState>(stateMachine->getCurState());
            if (state) {
                state->setSelectItem(item);
            }
        }
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
