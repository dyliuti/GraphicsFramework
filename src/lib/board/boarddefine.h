//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_DEFINE_H
#define BOARD_DEFINE_H

#include "board_global.h"
#include "view/scene.h"
#include <QPointF>
#include <set>

BOARD_NAMESPACE_BEGIN
class Scene;
enum class StateType {
    Undefined = -1,
    Normal = 0, // 仅是鼠标移动，不做选择也不做绘制
    BoxSelect,
    SingleSelect,
    Pen, //  粉笔
    Eraser, // 橡皮擦
};
static std::set<StateType> s_editTypeSet { StateType::Pen, StateType::Eraser };

enum class ToolType {
    Cursor, // 仅是鼠标移动
    Select,
    Pen,
};

class StateCommonData {
public:
    QPointF pressPos;
    Scene* scene = nullptr;
};

static int s_sceneWidth = 1600;
static int s_sceneHeight = 1200;
static int s_guideLineWidth = 800;
static int s_guideLineHeight = 800;

BOARD_NAMESPACE_END

#endif // BOARD_DEFINE_H
