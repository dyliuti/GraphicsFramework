//
// Created by xukong on 2022/3/11.
//

#pragma once

#include "middleware/common/macros.h"
#include "middleware/render/texture.h"

NAMESPACE_MIDDLEWARE_BEGIN

enum MediaDataType {
    kMediaDataDefault = 0,
    kMediaDataVideoBase = 0x20,
    KMediaDataVideoRGBA,
    kMediaDataVideoRawGLTexture,
    kMediaDataEOS = 0x40,
};

struct Transform {
    int32_t rotation = 0;
    bool mirror = false;
    bool verticalFlip = false;
    uint32_t scaledWidth = 0;
    uint32_t scaledHeight = 0;
    float cropWidthFrac = 1.0;
    float cropHeightFrac = 1.0;
    float cropXFrac = 0;
    float cropYFrac = 0;
};

struct VideoFrame {
   public:
    VideoFrame(MediaDataType t, std::shared_ptr<render::gl::Texture> tex, uint32_t w, uint32_t h)
        : type(t), texture(tex), width(w), height(h) {}
    MediaDataType type;
    Transform transform;
    // unit ms
    uint64_t pts;
    uint32_t width;
    uint64_t height;
    std::shared_ptr<render::gl::Texture> texture;
    std::shared_ptr<uint8_t> data;
};

NAMESPACE_MIDDLEWARE_END