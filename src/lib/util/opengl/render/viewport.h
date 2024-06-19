//
// Created by xukong on 2022/3/11.
//

#pragma once
#include <memory>
#include "middleware/common/macros.h"

NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {

enum DisplayLayout {
    kLayoutNone = 0,
    kLayoutAspectFit,
    kLayoutFixWidth,
    kLayoutFixHeight,
    kLayoutAspectFill
};

struct ViewPort {
    ViewPort(uint32_t w, uint32_t h)
        : width(w), height(h) {}
    ViewPort(uint32_t px, uint32_t py, uint32_t vx, uint32_t vy)
        : positionX(px), positionY(py), width(vx), height(vy) {}
    ViewPort(uint32_t w, uint32_t h, DisplayLayout layout)
        : width(w), height(h), displayLayout(layout) {}
    ViewPort(uint32_t px, uint32_t py, uint32_t vx, uint32_t vy, DisplayLayout layout)
        : positionX(px), positionY(py), width(vx), height(vy), displayLayout(layout) {}
    ViewPort(const ViewPort& viewport)
        : positionX(viewport.positionX), positionY(viewport.positionY), width(viewport.width), height(viewport.height), displayLayout(viewport.displayLayout), isBoundingSize(viewport.isBoundingSize) {}

    ViewPort TargetFinalViewport(uint32_t target_width, uint32_t target_height) const {
        if (isBoundingSize) {
            ViewPort final_view_port(*this);
            final_view_port.isBoundingSize = false;
            if (1.f * target_height / target_width > 1.f * height / width) {
                final_view_port.width = 1.f * height / target_height * target_width;
                final_view_port.height = height;
            } else {
                final_view_port.width = width;
                final_view_port.height = 1.f * width / target_width * target_height;
            }

            return final_view_port;
        } else {
            return *this;
        }
    }

    uint32_t positionX = 0;
    uint32_t positionY = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    bool isBoundingSize = false;
    DisplayLayout displayLayout = DisplayLayout::kLayoutAspectFit;
};
}  // namespace render::gl

NAMESPACE_MIDDLEWARE_END