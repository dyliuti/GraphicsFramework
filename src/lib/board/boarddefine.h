//
// Created by yanminwei on 2024/2/19.
//
#ifndef BOARD_DEFINE_H
#define BOARD_DEFINE_H

#include "board_global.h"
#include "view/scene.h"
#include <QGraphicsItem>
#include <QPointF>
#include <set>

BOARD_NAMESPACE_BEGIN
class Scene;
enum class BOARD_EXPORT StateType {
    Undefined = -1,
    Normal = 0, // 仅是鼠标移动，不做选择也不做绘制
    Select,
    BoxSelect,
    Pen, //  粉笔
    Eraser, // 橡皮擦
    Rect,
    Star,
    Cirle,
    Ellipse,
};
static std::set<StateType> s_editTypeSet { StateType::Pen, StateType::Eraser };

class StateCommonData {
public:
    QPointF pressStartPos;
};

static int s_sceneWidth = 1600;
static int s_sceneHeight = 1200;
static int s_guideLineWidth = 800;
static int s_guideLineHeight = 800;

const int ResizableRectType = QGraphicsItem::UserType + 1;
const int ResizableEllipseType = QGraphicsItem::UserType + 2;
const int ResizablePixmapType = QGraphicsItem::UserType + 3;
const int ResizableStarType = QGraphicsItem::UserType + 4;
const int StrokeType = QGraphicsItem::UserType + 5;

BOARD_NAMESPACE_END

#endif // BOARD_DEFINE_H
